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
    const glm::vec3 getPosition() const;

    void move(const glm::vec3& direction);

    const glm::vec3& getUp() const;
    const glm::vec3& getFront() const;

    void setYaw(double yaw);
    void setPitch(double pitch);
    double getYaw() const;
    double getPitch() const;

    void updateFront();
  private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::mat4 m_projectionMatrix;
    double m_yaw;
    double m_pitch;
    float m_speed;

};