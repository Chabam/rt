#include "engine.h"

#include <chrono>
#include <functional>
#include <glm/gtc/type_ptr.hpp>
#include <logger/logger.h>
#include <thread>

Engine::Engine(const Window& window)
    : m_window(window)
    , m_fps(60)
{
}

void Engine::init()
{
    Logger::info("Starting program!");

    // GLFW
    m_window.init();
    {
        using namespace std::placeholders;
        m_window.setKeyPressCallback(std::bind(Engine::handleKeyPress, this, _1));
        m_window.setResizeCallback(std::bind(Engine::handleResize, this, _1, _2));
    }
    // Move this somewhere else
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(handleGlError, nullptr);
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

void Engine::handleKeyPress(Engine* engine, int keyCode)
{
    switch (keyCode)
    {
    case GLFW_KEY_Q:
        Logger::info("Closing!");
        engine->m_window.setToClose();
        break;
    }
}

void Engine::handleResize(Engine* engine, int width, int height)
{
    engine->m_window.setSize(width, height);
    engine->m_scene.changeProjectionMatrix(
        glm::perspective(glm::radians(90.f), static_cast<float>(width) / height, 0.1f, 100.0f));
    engine->m_scene.render();
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