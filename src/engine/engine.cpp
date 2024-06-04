#include <rt/engine/engine.hpp>
#include <rt/utils/logger.hpp>

#include <GLFW/glfw3.h>
#include <chrono>
#include <format>
#include <functional>
#include <glad/gl.h>
#include <ratio>
#include <thread>

static constexpr auto NAME = "rt";

Engine::Engine()
    : m_window()
    , m_scene()
    , m_target_fps(60)
    , m_frame_count()
    , m_frame_time()
    , m_mouse_info()
    , m_keyboard_info()
{
}

void Engine::start()
{
    if (m_scene.empty())
    {
        m_logger.warn("Nothing to draw!");
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(handle_gl_error, nullptr);

    auto last_frame = std::chrono::system_clock::now();
    auto start_fps_count_timer = std::chrono::system_clock::now();
    glEnable(GL_DEPTH_TEST);
    while (!m_window->should_close())
    {
        using namespace std::chrono_literals;

        auto before_render = std::chrono::system_clock::now();

        constexpr glm::vec4 BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
        glClearColor(BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_scene.render();
        m_window->swap_buffers();

        const auto after_render = std::chrono::system_clock::now();
        m_frame_time = std::chrono::duration<double>(after_render - last_frame);
        last_frame = after_render;

        glfwPollEvents();
        process_inputs();

        ++m_frame_count;
        if (after_render - start_fps_count_timer > 1s)
        {
            m_window->set_title(std::vformat("rt: {} fps", std::make_format_args(m_frame_count)).c_str());
            m_frame_count = 0;
            start_fps_count_timer = std::chrono::system_clock::now();
        }

        const auto elapsed = after_render - before_render;
        const auto max_time_per_frame = std::chrono::nanoseconds(1s) / m_target_fps;
        const auto time_until_next_frame = after_render + (max_time_per_frame - elapsed);

        if (std::chrono::system_clock::now() < time_until_next_frame)
        {
            std::this_thread::sleep_until(time_until_next_frame);
        }
    }
}

void Engine::create_window(unsigned int width, unsigned int height, const char* title)
{
    m_logger.debug("Init glfw");
    if (!glfwInit())
    {
        throw std::runtime_error("Could not initialize GLWF!");
    }
    m_logger.debug("glfw ok!");

    m_window = std::make_unique<Window>(width, height, title);

    using namespace std::placeholders;
    m_window->set_resize_callback(std::bind(&Engine::on_resize, this, _1, _2));
    m_window->set_key_press_callback(std::bind(&Engine::on_key_press, this, _1, _2));
    m_window->set_mouse_button_pressed_callback(std::bind(&Engine::on_mouse_pressed, this, _1, _2, _3));
    m_window->set_mouse_pos_changed_callback(std::bind(&Engine::on_mouse_pos_changed, this, _1, _2));

    m_logger.debug("Init glad");
    if (!gladLoadGL(static_cast<GLADloadfunc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Could not initialize glad!");
    }
    m_logger.debug("glad ok!");
}

void Engine::set_scene(const Scene& scene)
{
    m_scene = scene;
}

void Engine::process_inputs()
{
    Camera& camera = m_scene.get_camera();
    camera.set_speed(m_frame_time.count() * 2.5f);

    if (m_keyboard_info.m_forward_key_pressed)
    {
        camera.move(camera.get_front());
    }

    if (m_keyboard_info.m_backward_key_pressed)
    {
        camera.move(-camera.get_front());
    }

    if (m_keyboard_info.m_left_key_pressed)
    {
        camera.move(-glm::normalize(glm::cross(camera.get_front(), camera.get_up())));
    }

    if (m_keyboard_info.m_right_key_pressed)
    {
        camera.move(glm::normalize(glm::cross(camera.get_front(), camera.get_up())));
    }

    if (m_keyboard_info.m_up_key_pressed)
    {
        camera.move(camera.get_up());
    }

    if (m_keyboard_info.m_down_key_pressed)
    {
        camera.move(-camera.get_up());
    }
}

void Engine::on_key_press(int keyCode, int action)
{
    const bool is_pressed_action = action != GLFW_RELEASE;

    switch (keyCode)
    {
    case GLFW_KEY_UP:
    case GLFW_KEY_W:
        m_keyboard_info.m_forward_key_pressed = is_pressed_action;
        break;
    case GLFW_KEY_DOWN:
    case GLFW_KEY_S:
        m_keyboard_info.m_backward_key_pressed = is_pressed_action;
        break;
    case GLFW_KEY_LEFT:
    case GLFW_KEY_A:
        m_keyboard_info.m_left_key_pressed = is_pressed_action;
        break;
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_D:
        m_keyboard_info.m_right_key_pressed = is_pressed_action;
        break;
    case GLFW_KEY_SPACE:
        m_keyboard_info.m_up_key_pressed = is_pressed_action;
        break;
    case GLFW_KEY_LEFT_SHIFT:
        m_keyboard_info.m_down_key_pressed = is_pressed_action;
        break;
    case GLFW_KEY_ESCAPE:
        m_logger.info("Closing!");
        m_window->close();
        break;
    }
}

void Engine::on_mouse_pos_changed(double x_pos, double y_pos)
{
    if (m_mouse_info.m_pressed)
    {
        double delta_x = x_pos - m_mouse_info.m_last_x;
        double delta_y = m_mouse_info.m_last_y - y_pos;

        constexpr auto sensitivity = 0.1f;

        delta_x *= sensitivity;
        delta_y *= sensitivity;

        Camera& camera = m_scene.get_camera();
        camera.set_yaw(camera.get_yaw() + delta_x);
        camera.set_pitch(camera.get_pitch() + delta_y);
        camera.update_front();
    }

    m_mouse_info.m_last_x = x_pos;
    m_mouse_info.m_last_y = y_pos;
}

void Engine::on_mouse_pressed(int key, int action, int mod)
{
    m_mouse_info.m_pressed = key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
}

void Engine::on_resize(int width, int height)
{
    if (height == 0 || width == 0)
    {
        return;
    }
    glViewport(0, 0, width, height);
    m_scene.get_camera().set_aspect_ratio(width, height);
    m_scene.render();
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