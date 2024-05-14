#pragma once

#include <glm/vec3.hpp>

struct Material
{
    glm::vec3 m_color = glm::vec3(1.f);
    float m_specular = 0.f;
    uint32_t m_shininess = 1;
    bool m_emitsLight = false;
};
