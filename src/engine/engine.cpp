#include "glm/ext/vector_float4.hpp"

#include <rt/engine/engine.hpp>
#include <rt/engine/engine_component.hpp>
#include <rt/engine/time_step.hpp>
#include <rt/utils/logger.hpp>

#include <GLFW/glfw3.h>
#include <chrono>
#include <format>
#include <memory>
#include <stdexcept>

namespace rt
{

static constexpr auto NAME = "rt";

Engine::Engine()
    : m_target_fps{60}
    , m_frame_count{}
{
}

void Engine::render(Window& window, Scene& scene)
{
    if (scene.empty())
    {
        m_logger.warn("Nothing to draw!");
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(handle_gl_error, nullptr);

    auto last_frame = std::chrono::system_clock::now();
    auto start_fps_count_timer = std::chrono::system_clock::now();
    glEnable(GL_DEPTH_TEST);

    const char* original_title = window.get_title();

    while (!window.should_close())
    {
        using namespace std::chrono_literals;

        auto before_render = std::chrono::system_clock::now();

        constexpr glm::vec4 BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
        glClearColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.render();
        window.update();

        TimeStep time_step;
        const auto after_render = std::chrono::system_clock::now();
        time_step.m_render_time = after_render - last_frame;
        last_frame = after_render;

        const auto elapsed = after_render - before_render;
        const auto max_time_per_frame = std::chrono::system_clock::duration(1s) / m_target_fps;
        time_step.m_next_frame_deadline = after_render + (max_time_per_frame - elapsed);

        for (const int pressed_key : window.get_keyboard_info().m_current_pressed_keys)
        {
            if (pressed_key == GLFW_KEY_ESCAPE || pressed_key == GLFW_KEY_Q)
            {
                m_logger.info("Closing!");
                window.close();
            }
        }

        for (const auto& engine_component : m_engine_components)
        {
            engine_component->update(time_step);
        }

        ++m_frame_count;
        if (after_render - start_fps_count_timer > 1s)
        {
            window.set_title(std::vformat("{}: {} fps", std::make_format_args(original_title, m_frame_count)).c_str());
            m_frame_count = 0;
            start_fps_count_timer = std::chrono::system_clock::now();
        }

        while(std::chrono::system_clock::now() < time_step.m_next_frame_deadline);
    }
}

void Engine::register_engine_component(const std::shared_ptr<EngineComponent>& engine_component)
{
    m_engine_components.push_back(engine_component);
}

void Engine::handle_gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                             const GLchar* message, const void* user_param)
{
    Logger::Level level;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        level = Logger::Level::Error;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        level = Logger::Level::Warn;
        break;
    default:
    case GL_DEBUG_SEVERITY_LOW:
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        level = Logger::Level::Debug;
        return;
    }
    Logger{"OpenGL"}.log(level, "{}", message);

    throw std::runtime_error("OpenGL fatal error!");
}

} // namespace rt
