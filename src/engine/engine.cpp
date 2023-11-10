#include "engine.h"

#include <GLFW/glfw3.h>
#include <chrono>
#include <functional>
#include <glad/glad.h>
#include <ratio>
#include <utils/logger.h>

Engine::Engine()
    : m_window(1280, 720, "rt")
    , m_scene()
    , m_fps(60)
    , m_frameTime()
    , m_mouseInfo()
    , m_keyboardInfo()
{
    using namespace std::placeholders;
    m_window.setResizeCallback(std::bind(&Engine::handleResize, this, _1, _2));
    m_window.setKeyPressCallback(std::bind(&Engine::handleKeyPress, this, _1, _2));
    m_window.setMouseButtonPressedCallback(std::bind(&Engine::handleMouseButtonPressed, this, _1, _2, _3));
    m_window.setMousePositionChangedCallback(std::bind(&Engine::handleMousePositionChanged, this, _1, _2));

    Logger::debug("Init glad");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Could not initialize glad!");
    }
    Logger::debug("glad ok!");

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(handleGlError, nullptr);
}

void Engine::init()
{

    Logger::debug("Init glfw");
    if (!glfwInit())
    {
        throw std::runtime_error("Could not initialize GLWF!");
    }
    Logger::debug("glfw ok!");
}

void Engine::start()
{
    if (m_scene.empty())
    {
        Logger::warn("Nothing to draw!");
        return;
    }

    auto lastFrame = std::chrono::system_clock::now();
    glEnable(GL_DEPTH_TEST);
    while (!m_window.shouldClose())
    {
        auto beforeRender = std::chrono::system_clock::now();

        constexpr glm::vec4 BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
        glClearColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_scene.render();
        m_window.swapBuffers();

        const auto afterRender = std::chrono::system_clock::now();
        m_frameTime = std::chrono::duration<double>(afterRender - lastFrame);
        lastFrame = afterRender;


        glfwPollEvents();
        processInputs();

        const auto elapsed = afterRender - beforeRender;
        const auto maxTimePerFrame = std::chrono::seconds(1) / m_fps;
        const auto timeUntilNextFrame = afterRender + (maxTimePerFrame - elapsed);

        Logger::debug("Frame took: ") << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(elapsed);

        std::this_thread::sleep_until(timeUntilNextFrame);
    }
}

void Engine::setScene(const Scene& scene)
{
    m_scene = scene;
}

void Engine::processInputs()
{
    Camera& camera = m_scene.getCamera();
    camera.setSpeed(m_frameTime.count() * 2.5f);

    if (m_keyboardInfo.m_forwardKeyPressed)
    {
        camera.move(camera.getFront());
    }

    if (m_keyboardInfo.m_backwardKeyPressed)
    {
        camera.move(-camera.getFront());
    }

    if (m_keyboardInfo.m_leftKeyPressed)
    {
        camera.move(-glm::normalize(glm::cross(camera.getFront(), camera.getUp())));
    }

    if (m_keyboardInfo.m_rightKeyPressed)
    {
        camera.move(glm::normalize(glm::cross(camera.getFront(), camera.getUp())));
    }

    if (m_keyboardInfo.m_upKeyPressed)
    {
        camera.move(camera.getUp());
    }

    if (m_keyboardInfo.m_downKeyPressed)
    {
        camera.move(-camera.getUp());
    }
}

void Engine::handleKeyPress(int keyCode, int action)
{
    const bool isPressed = action != GLFW_RELEASE;

    switch (keyCode)
    {
    case GLFW_KEY_UP:
    case GLFW_KEY_W:
        m_keyboardInfo.m_forwardKeyPressed = isPressed;
        break;
    case GLFW_KEY_DOWN:
    case GLFW_KEY_S:
        m_keyboardInfo.m_backwardKeyPressed = isPressed;
        break;
    case GLFW_KEY_LEFT:
    case GLFW_KEY_A:
        m_keyboardInfo.m_leftKeyPressed = isPressed;
        break;
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_D:
        m_keyboardInfo.m_rightKeyPressed = isPressed;
        break;
    case GLFW_KEY_SPACE:
        m_keyboardInfo.m_upKeyPressed = isPressed;
        break;
    case GLFW_KEY_LEFT_SHIFT:
        m_keyboardInfo.m_downKeyPressed = isPressed;
        break;
    case GLFW_KEY_ESCAPE:
        Logger::info("Closing!");
        m_window.setToClose();
        break;
    }
}

void Engine::handleMousePositionChanged(double xPos, double yPos)
{
    if (m_mouseInfo.m_pressed)
    {
        double deltaX = xPos - m_mouseInfo.m_lastX;
        double deltaY = m_mouseInfo.m_lastY - yPos;

        constexpr auto sensitivity = 0.1f;

        deltaX *= sensitivity;
        deltaY *= sensitivity;

        Camera& camera = m_scene.getCamera();
        camera.setYaw(camera.getYaw() + deltaX);
        camera.setPitch(camera.getPitch() + deltaY);
        camera.updateFront();
    }

    m_mouseInfo.m_lastX = xPos;
    m_mouseInfo.m_lastY = yPos;
}

void Engine::handleMouseButtonPressed(int key, int action, int mod)
{
    m_mouseInfo.m_pressed = key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
}

void Engine::handleResize(int width, int height)
{
    if (height == 0 || width == 0)
    {
        return;
    }
    glViewport(0, 0, width, height);
    m_scene.getCamera().setAspectRatio(width, height);
    m_scene.render();
}

void Engine::handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                           const GLchar* message, const void* userParam)
{
    Logger::Level level;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        level = Logger::Level::ERROR;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        level = Logger::Level::WARN;
        break;
    default:
    case GL_DEBUG_SEVERITY_LOW:
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        level = Logger::Level::DEBUG;
        return;
    }
    Logger(level) << "OpenGL: " << message;

    throw std::runtime_error("OpenGL fatal error!");
}