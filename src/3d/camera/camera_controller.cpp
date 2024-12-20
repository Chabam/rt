#include <rt/3d/camera/camera.hpp>
#include <rt/3d/camera/camera_controller.hpp>
#include <rt/engine/time_step.hpp>
#include <rt/graphics/window/window.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>

namespace rt
{

CameraController::CameraController(Camera& camera, const Window& window)
    : m_camera{camera}
    , m_window{window}
    , m_mouse_info_cache{}
{
}

void CameraController::update(const TimeStep& time_step)
{
    bool forward_key_pressed = false;
    bool backward_key_pressed = false;
    bool left_key_pressed = false;
    bool right_key_pressed = false;
    bool up_key_pressed = false;
    bool down_key_pressed = false;
    for (const int key_code : m_window.get_keyboard_info().m_current_pressed_keys)
    {
        switch (key_code)
        {
        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            forward_key_pressed = true;
            break;
        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            backward_key_pressed = true;
            break;
        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            left_key_pressed = true;
            break;
        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            right_key_pressed = true;
            break;
        case GLFW_KEY_SPACE:
            up_key_pressed = true;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            down_key_pressed = true;
            break;
        }
    }

    constexpr float speed_increase = 2.5f;
    m_camera.set_speed(std::chrono::duration_cast<std::chrono::duration<double>>(time_step.m_render_time).count() * speed_increase);

    if (forward_key_pressed)
        m_camera.move(m_camera.get_front());
    if (backward_key_pressed)
        m_camera.move(-m_camera.get_front());
    if (left_key_pressed)
        m_camera.move(-glm::normalize(glm::cross(m_camera.get_front(), m_camera.get_up())));
    if (right_key_pressed)
        m_camera.move(glm::normalize(glm::cross(m_camera.get_front(), m_camera.get_up())));
    if (up_key_pressed)
        m_camera.move(m_camera.get_up());
    if (down_key_pressed)
        m_camera.move(-m_camera.get_up());

    const auto& mouse_info = m_window.get_mouse_info();
    if (std::ranges::find(mouse_info.m_current_pressed_buttons, GLFW_MOUSE_BUTTON_RIGHT) !=
        mouse_info.m_current_pressed_buttons.end())
    {
        double delta_x = mouse_info.x_pos - m_mouse_info_cache.m_last_x;
        double delta_y = m_mouse_info_cache.m_last_y - mouse_info.y_pos;

        constexpr auto sensitivity = 0.1f;

        delta_x *= sensitivity;
        delta_y *= sensitivity;

        m_camera.set_yaw(m_camera.get_yaw() + delta_x);
        m_camera.set_pitch(m_camera.get_pitch() + delta_y);
        m_camera.update_front();
    }

    m_mouse_info_cache.m_last_x = mouse_info.x_pos;
    m_mouse_info_cache.m_last_y = mouse_info.y_pos;

    const unsigned int new_width = m_window.get_width();
    const unsigned int new_height = m_window.get_height();

    if (m_window_info_cache.m_last_width != new_width || m_window_info_cache.m_last_height == new_height)
    {
        m_camera.set_aspect_ratio(new_width, new_height);
    }

    m_window_info_cache.m_last_width = new_width;
    m_window_info_cache.m_last_height = new_height;
}

} // namespace rt
