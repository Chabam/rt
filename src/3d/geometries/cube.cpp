#include <rt/3d/geometries/cube.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

namespace rt
{

Cube::Cube(float width, float height, float depth, const std::shared_ptr<Material>& material,
           const std::shared_ptr<Texture>& texture)
    : Mesh{material, texture}
    , m_quads{}
{
    set_model(glm::scale(m_model, glm::vec3(width, height, depth)));

    constexpr glm::vec3 p1 = {1.f, 1.f, -1.f};
    constexpr glm::vec3 p2 = {1.f, 1.f, 1.f};
    constexpr glm::vec3 p3 = {1.f, -1.f, 1.f};
    constexpr glm::vec3 p4 = {1.f, -1.f, -1.f};
    constexpr glm::vec3 p5 = {-1.f, 1.f, 1.f};
    constexpr glm::vec3 p6 = {-1.f, 1.f, -1.f};
    constexpr glm::vec3 p7 = {-1.f, -1.f, -1.f};
    constexpr glm::vec3 p8 = {-1.f, -1.f, 1.f};

    m_quads = {
        Quad{{p1, p2, p3, p4}}, // RIGHT
        Quad{{p5, p6, p7, p8}}, // LEFT
        Quad{{p6, p5, p2, p1}}, // TOP
        Quad{{p7, p8, p3, p4}}, // BOTTOM
        Quad{{p6, p1, p4, p7}}, // FRONT
        Quad{{p2, p5, p8, p3}}  // BACK
    };

    constexpr auto quad_count = std::tuple_size_v<decltype(m_quads)>;
    std::array<Vertex, quad_count * Quad::POINT_COUNT> vertices;
    std::array<unsigned short, quad_count * Quad::VERTEX_COUNT> indices;

    auto vertices_offset = 0;
    auto indices_offset = 0;
    for (const Quad& quad : m_quads)
    {
        std::ranges::transform(quad.m_indices, indices.begin() + indices_offset,
                               [vertices_offset](unsigned short idx) { return idx + vertices_offset; });
        indices_offset += Quad::VERTEX_COUNT;

        std::ranges::move(quad.m_vertices, vertices.begin() + vertices_offset);
        vertices_offset += Quad::POINT_COUNT;
    }
    m_buffer = std::make_unique<Buffer>(vertices, indices);
}

unsigned int Cube::get_triangle_count() const
{
    return m_quads.size() * Quad::TRIANGLE_COUNT;
}

} // namespace rt