#pragma once
#include <glm/vec3.hpp>

struct Light
{
    float m_ambient;
    glm::vec3 m_pos;
    glm::vec3 m_color;
};