#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"

namespace rt
{

class Camera
{
  public:
    Camera();

    void set_aspect_ratio(unsigned int width, unsigned int height);
    const glm::mat4 get_projection() const;
    const glm::mat4 get_view() const;
    const glm::vec3 get_position() const;

    void move(const glm::vec3& direction);

    const glm::vec3& get_up() const;
    const glm::vec3& get_front() const;

    void set_yaw(double yaw);
    void set_pitch(double pitch);
    double get_yaw() const;
    double get_pitch() const;

    void set_speed(float speed);

    void update_front();

  private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::mat4 m_projection;
    double m_yaw;
    double m_pitch;
    float m_speed;
};

} // namespace rt

#endif // RT_CAMERA_H