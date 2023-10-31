#include "engine.h"

#include <chrono>
#include <functional>
#include <glm/gtc/type_ptr.hpp>
#include <logger/logger.h>
#include <thread>

Engine::Engine(const Shader &shader, const Window &window)
    : m_window(window)
    , m_shader(shader)
    , m_fps(60)
{
}

Engine::RenderTarget::RenderTarget(const Mesh &mesh, Buffer &&buffer)
    : m_mesh(mesh)
    , m_buffer(std::move(buffer))
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

    m_shader.init();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(handleGlError, nullptr);
}

void Engine::start()
{
    if (m_renderTargets.empty())
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

        render();
        glfwPollEvents();

        auto afterRender = std::chrono::system_clock::now();
        miliseconds elapsed = afterRender - beforeRender;
        const miliseconds maxTimePerFrame(1000ms / m_fps);

        std::this_thread::sleep_for(maxTimePerFrame - elapsed);
    }
}

void Engine::render()
{
    static glm::vec4 BLACK = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(BLACK));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (RenderTarget &renderTarget : m_renderTargets)
    {
        m_shader.bind();
        m_shader.setUniforms(renderTarget.m_mesh.getMaterial(), renderTarget.m_mesh.getModel(), VIEW_MATRIX,
                             PROJECTION_MATRIX);
        glDrawArrays(GL_TRIANGLES, 0, renderTarget.m_mesh.getTriangleCount() * 3);
        m_shader.unbind();
    }

    m_window.swapBuffers();
}

void Engine::setMeshes(const std::vector<Mesh> &meshes)
{
    for (const Mesh &mesh : meshes)
    {
        m_renderTargets.emplace_back(mesh, mesh.getVertices());
    }
}

void Engine::handleKeyPress(Engine *engine, int keyCode)
{
    switch (keyCode)
    {
    case GLFW_KEY_Q:
        Logger::info("Closing!");
        engine->m_window.setToClose();
        break;
    case GLFW_KEY_R:
        Logger::info("Reloading shaders");
        engine->m_shader.reload();
        break;
    }
}

void Engine::handleResize(Engine *engine, int width, int height)
{
    engine->m_window.setSize(width, height);
    engine->PROJECTION_MATRIX = glm::perspective(glm::radians(90.f), static_cast<float>(width) / height, 0.1f, 100.0f);
    engine->render();
}

void Engine::handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                           const GLchar *message, const void *userParam)
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