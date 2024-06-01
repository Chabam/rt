#ifndef RT_VERTICE_BUFFER_DATA_H
#define RT_VERTICE_BUFFER_DATA_H

#include <array>
#include <glad/gl.h>
#include <glm/vec3.hpp>

struct VertexAttributeLayout
{
    GLuint m_location;
    GLuint m_count;
    GLenum m_type;
    GLuint m_offset;
};

struct Vertex
{
    static constexpr auto ATTRIBUTES_COUNT = 2U;

    glm::vec3 m_position;
    glm::vec3 m_normal;

    constexpr static std::array<VertexAttributeLayout, ATTRIBUTES_COUNT> get_attributes_layout()
    {
        auto location = 0U;
        // clang-format off
        return
        {
            {
                {
                    .m_location = location++,
                    .m_count = decltype(Vertex::m_position)::length(),
                    .m_type = GL_FLOAT,
                    .m_offset = 0
                },
                {
                    .m_location = location++,
                    .m_count = decltype(Vertex::m_normal)::length(),
                    .m_type = GL_FLOAT,
                    .m_offset = sizeof(Vertex::m_position)
                }
            }
        };
        // clang-format on
    }
};

#endif // RT_VERTICE_BUFFER_DATA_H
