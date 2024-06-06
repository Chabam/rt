#ifndef RT_LIGHT_H
#define RT_LIGHT_H

#include "glm/ext/vector_float3.hpp"

namespace rt
{

struct Light
{
    float m_ambient;
    glm::vec3 m_pos;
    glm::vec3 m_color;
};

} // namespace rt

#endif // RT_LIGHT_H