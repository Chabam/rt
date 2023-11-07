#include "camera.h"

#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
    : m_position(0, 0, 4)
    , m_front(0, 0, -1)
    , m_up(0, 1, 0)
    , m_projectionMatrix(glm::perspective(glm::radians(90.f), 16 / 9.f, 0.1f, 100.0f))
    , m_yaw(-90.0)
    , m_pitch()
    , m_speed(0.05f)
{
}

void Camera::setAspectRatio(unsigned int width, unsigned int height)
{
    m_projectionMatrix = glm::perspective(glm::radians(90.f), static_cast<float>(width) / height, 0.1f, 100.0f);
}

const glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

const glm::mat4 Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}

const glm::vec3 Camera::getPosition() const
{
    return m_position;
}

void Camera::move(const glm::vec3& direction)
{
    m_position += m_speed * direction;
}

const glm::vec3& Camera::getUp() const
{
    return m_up;
}

const glm::vec3& Camera::getFront() const
{
    return m_front;
}

double Camera::getYaw() const
{
    return m_yaw;
}

double Camera::getPitch() const
{
    return m_pitch;
}

void Camera::setYaw(double yaw)
{
    m_yaw = std::min(89.0, yaw);
}

void Camera::setPitch(double pitch)
{
    m_pitch = std::max(-89.0, pitch);
}

void Camera::updateFront()
{
    m_front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_front.y = std::sin(glm::radians(m_pitch));
    m_front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));

    glm::normalize(m_front);
}