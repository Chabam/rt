#include <rt/3d/geometries/cube.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

namespace rt
{

Cube::Cube(float width, float height, float depth)
    : m_width{width}
    , m_height{height}
    , m_depth{depth}
    , m_quads{}
{
    const auto scale_vector = glm::vec3(width, height, depth);
    const glm::vec3 p1 = scale_vector * glm::vec3{1.f, 1.f, -1.f};
    const glm::vec3 p2 = scale_vector * glm::vec3{1.f, 1.f, 1.f};
    const glm::vec3 p3 = scale_vector * glm::vec3{1.f, -1.f, 1.f};
    const glm::vec3 p4 = scale_vector * glm::vec3{1.f, -1.f, -1.f};
    const glm::vec3 p5 = scale_vector * glm::vec3{-1.f, 1.f, 1.f};
    const glm::vec3 p6 = scale_vector * glm::vec3{-1.f, 1.f, -1.f};
    const glm::vec3 p7 = scale_vector * glm::vec3{-1.f, -1.f, -1.f};
    const glm::vec3 p8 = scale_vector * glm::vec3{-1.f, -1.f, 1.f};

    m_quads = {
        Quad{{p1, p2, p3, p4}}, // RIGHT
        Quad{{p5, p6, p7, p8}}, // LEFT
        Quad{{p6, p5, p2, p1}}, // TOP
        Quad{{p7, p8, p3, p4}}, // BOTTOM
        Quad{{p6, p1, p4, p7}}, // FRONT
        Quad{{p2, p5, p8, p3}}  // BACK
    };

    auto vertices_offset = 0;
    auto indices_offset = 0;
    for (const Quad& quad : m_quads)
    {
        std::ranges::transform(quad.get_indices(), m_indices.begin() + indices_offset,
                               [vertices_offset](unsigned short idx) { return idx + vertices_offset; });
        indices_offset += Quad::VERTEX_COUNT;

        std::ranges::move(quad.get_vertices(), m_vertices.begin() + vertices_offset);
        vertices_offset += Quad::POINT_COUNT;
    }
}

std::span<const Vertex> Cube::get_vertices() const
{
    return m_vertices;
}

std::span<const unsigned short> Cube::get_indices() const
{
    return m_indices;
}

} // namespace rt