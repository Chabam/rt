#include "camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
    : m_position(0, 0, 4)
    , m_front(0, 0, -1)
    , m_up(0, 1, 0)
    , m_projectionMatrix(glm::perspective(glm::radians(90.f), 16 / 9.f, 0.1f, 100.0f))
    , m_speed(0.1f)
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

void Camera::move(const glm::vec3& direction)
{
    m_position += m_speed * direction;
}

const glm::vec3& Camera::getUp()
{
    return m_up;
}

const glm::vec3& Camera::getFront()
{
    return m_front;
}