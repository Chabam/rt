#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
  public:
    Camera();

    void setAspectRatio(unsigned int width, unsigned int height);
    const glm::mat4 getProjectionMatrix() const;
    const glm::mat4 getViewMatrix() const;
    void move(const glm::vec3& direction);
    const glm::vec3& getUp();
    const glm::vec3& getFront();
  private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::mat4 m_projectionMatrix;
    float m_speed;
};