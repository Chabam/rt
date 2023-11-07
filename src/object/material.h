#pragma once

#include <glm/vec3.hpp>

class Material
{
  public:
    Material(const glm::vec3& color = glm::vec3(1.f, 0.f, 0.f), float specular = 0);
    Material(const Material& other);
    Material& operator=(const Material& other);

    glm::vec3 m_color;
    float m_specular;
};
