#include <rt/3d/geometries/cube.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <algorithm>
#include <cassert>
#include <glm/ext/matrix_transform.hpp>
#include <iterator>

Cube::Cube(float width, float height, float depth, const std::shared_ptr<Material>& material)
    : Mesh{material}
    , m_quads{}
{
    set_model(glm::scale(m_model, glm::vec3(width, height, depth)));

    constexpr std::array<std::tuple<glm::vec3, unsigned short>, POINT_COUNT> p = {
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{1.f, 1.f, -1.f}, 0),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{1.f, 1.f, 1.f}, 1),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{1.f, -1.f, 1.f}, 2),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{1.f, -1.f, -1.f}, 3),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{-1.f, 1.f, 1.f}, 4),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{-1.f, 1.f, -1.f}, 5),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{-1.f, -1.f, -1.f}, 6),
        std::make_tuple<glm::vec3, unsigned short>(glm::vec3{-1.f, -1.f, 1.f}, 7),
    };

    m_quads = {
        Quad{{p[0], p[1], p[2], p[3]}}, // RIGHT
        Quad{{p[4], p[5], p[6], p[7]}}, // LEFT
        Quad{{p[5], p[4], p[1], p[0]}}, // TOP
        Quad{{p[6], p[7], p[2], p[3]}}, // BOTTOM
        Quad{{p[5], p[0], p[3], p[6]}}, // FRONT
        Quad{{p[1], p[4], p[7], p[2]}}  // BACK
    };

    constexpr auto quad_count = std::tuple_size_v<decltype(m_quads)>;
    std::array<Vertex, quad_count * Quad::POINT_COUNT> vertices;
    std::array<unsigned short, quad_count * Quad::VERTEX_COUNT> indices;

    auto vertices_offset = 0;
    auto indices_offset = 0;
    for (const Quad& quad : m_quads)
    {
        std::ranges::move(quad.m_vertices, vertices.begin() + vertices_offset);
        vertices_offset += Quad::POINT_COUNT;

        std::ranges::move(quad.m_indices, indices.begin() + indices_offset);
        indices_offset += Quad::VERTEX_COUNT;
    }

    m_buffer = std::make_unique<Buffer>(vertices, indices);
}

uint32_t Cube::get_triangle_count() const
{
    return m_quads.size() * Quad::TRIANGLE_COUNT;
}
