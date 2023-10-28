#pragma once
#include "object/color.h"
#include <glm/glm.hpp>

class Material
{
  public:
    Material(const glm::vec4& color = glm::vec4(1.f, 0.f, 0.f, 1.f), float diffuse = 1, float specular = 1);
    Material(const Material &other);
    Material &operator=(const Material &other);

    glm::vec4 m_color;
    float m_diffuse;
    float m_specular;
};
