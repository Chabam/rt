#ifndef RT_VERTICE_BUFFER_DATA_H
#define RT_VERTICE_BUFFER_DATA_H

#include <array>
#include <glad/gl.h>
#include <glm/vec3.hpp>

struct VerticeBufferData
{
    glm::vec3 m_position;
    glm::vec3 m_normal;

    using FloatValues = std::array<GLfloat, decltype(m_position)::length() + decltype(m_normal)::length()>;
    operator FloatValues() const;
};

#endif // RT_VERTICE_BUFFER_DATA_H
