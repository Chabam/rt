#include <rt/3d/camera/camera.hpp>

#include <algorithm>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace rt
{

Camera::Camera()
    : m_position(0, 0, 4)
    , m_front(0, 0, -1)
    , m_up(0, 1, 0)
    , m_projection(glm::perspective(glm::radians(90.f), 16 / 9.f, 0.1f, 100.0f))
    , m_yaw(-90.0)
    , m_pitch()
    , m_speed(0.05f)
{
}

void Camera::set_aspect_ratio(unsigned int width, unsigned int height)
{
    m_projection = glm::perspective(glm::radians(90.f), static_cast<float>(width) / height, 0.1f, 100.0f);
}

const glm::mat4 Camera::get_view() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

const glm::mat4 Camera::get_projection() const
{
    return m_projection;
}

const glm::vec3 Camera::get_position() const
{
    return m_position;
}

void Camera::move(const glm::vec3& direction)
{
    m_position += m_speed * direction;
}

const glm::vec3& Camera::get_up() const
{
    return m_up;
}

const glm::vec3& Camera::get_front() const
{
    return m_front;
}

double Camera::get_yaw() const
{
    return m_yaw;
}

double Camera::get_pitch() const
{
    return m_pitch;
}

void Camera::set_yaw(double yaw)
{
    m_yaw = yaw;
}

void Camera::set_pitch(double pitch)
{
    m_pitch = std::clamp(pitch, -89.0, 89.0);
}

void Camera::update_front()
{
    m_front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_front.y = std::sin(glm::radians(m_pitch));
    m_front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));

    m_front = glm::normalize(m_front);
}

void Camera::set_speed(float speed)
{
    m_speed = speed;
}

} // namespace rt