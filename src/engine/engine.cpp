#include "engine.h"

#include <GLFW/glfw3.h>
#include <chrono>
#include <functional>
#include <glad/glad.h>
#include <utils/logger.h>

Engine::Engine()
    : m_window(1280, 720, "rt")
    , m_scene()
    , m_fps(60)
{
    using namespace std::placeholders;
    m_window.setResizeCallback(std::bind(&Engine::handleResize, this, _1, _2));
    m_window.setKeyPressCallback(std::bind(&Engine::handleKeyPress, this, _1));

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

    glEnable(GL_DEPTH_TEST);
    while (!m_window.shouldClose())
    {
        typedef std::chrono::duration<double, std::milli> miliseconds;
        using namespace std::chrono_literals;
        auto beforeRender = std::chrono::system_clock::now();

        constexpr glm::vec4 BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
        glClearColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_scene.render();
        m_window.swapBuffers();

        glfwPollEvents();

        auto afterRender = std::chrono::system_clock::now();
        miliseconds elapsed = afterRender - beforeRender;
        const miliseconds maxTimePerFrame(1000ms / m_fps);

        std::this_thread::sleep_for(maxTimePerFrame - elapsed);
    }
}

void Engine::setScene(const Scene& scene)
{
    m_scene = scene;
}

void Engine::handleKeyPress(int keyCode)
{
    Camera& camera = m_scene.getCamera();
    switch (keyCode)
    {
    case GLFW_KEY_UP:
    case GLFW_KEY_W:
        camera.move(camera.getFront());
        break;
    case GLFW_KEY_DOWN:
    case GLFW_KEY_S:
        camera.move(-camera.getFront());
        break;
    case GLFW_KEY_LEFT:
    case GLFW_KEY_A:
        camera.move(-glm::normalize(glm::cross(camera.getFront(), camera.getUp())));
        break;
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_D:
        camera.move(glm::normalize(glm::cross(camera.getFront(), camera.getUp())));
        break;
    case GLFW_KEY_ESCAPE:
        Logger::info("Closing!");
        m_window.setToClose();
        break;
    }
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