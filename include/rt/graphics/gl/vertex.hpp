#ifndef RT_VERTEX_H
#define RT_VERTEX_H

#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float2.hpp"
#include <array>
#include <glad/gl.h>

namespace rt
{

struct VertexAttributeLayout
{
    GLuint m_location;
    GLuint m_count;
    GLenum m_type;
    GLuint m_offset;
};

struct Vertex
{
    static constexpr auto ATTRIBUTES_COUNT = 5U;

    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_uv;
    glm::vec3 m_tangent;
    glm::vec3 m_bi_tangent;

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
                },
                {
                    .m_location = location++,
                    .m_count = decltype(Vertex::m_uv)::length(),
                    .m_type = GL_FLOAT,
                    .m_offset = sizeof(Vertex::m_position) + sizeof(Vertex::m_normal)
                },
                {
                    .m_location = location++,
                    .m_count = decltype(Vertex::m_tangent)::length(),
                    .m_type = GL_FLOAT,
                    .m_offset = sizeof(Vertex::m_position) + sizeof(Vertex::m_normal) + sizeof(Vertex::m_uv)
                },
                {
                    .m_location = location++,
                    .m_count = decltype(Vertex::m_bi_tangent)::length(),
                    .m_type = GL_FLOAT,
                    .m_offset = sizeof(Vertex::m_position) + sizeof(Vertex::m_normal) + sizeof(Vertex::m_uv) + sizeof(Vertex::m_tangent)
                }
            }
        };
        // clang-format on
    }
};

} // namespace rt

#endif // RT_VERTEX_H
