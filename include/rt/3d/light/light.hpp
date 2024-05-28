#ifndef RT_LIGHT_H
#define RT_LIGHT_H

#include <glm/vec3.hpp>

struct Light
{
    float m_ambient;
    glm::vec3 m_pos;
    glm::vec3 m_color;
};

#endif // RT_LIGHT_H