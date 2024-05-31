#include <rt/3d/geometries/cube.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <algorithm>
#include <cassert>
#include <glm/ext/matrix_transform.hpp>
#include <iterator>

std::array<Quad, 6> generate_default_quads()
{
    constexpr glm::vec3 p1 = {1.f, 1.f, -1.f};
    constexpr glm::vec3 p2 = {1.f, 1.f, 1.f};
    constexpr glm::vec3 p3 = {1.f, -1.f, 1.f};
    constexpr glm::vec3 p4 = {1.f, -1.f, -1.f};
    constexpr glm::vec3 p5 = {-1.f, 1.f, 1.f};
    constexpr glm::vec3 p6 = {-1.f, 1.f, -1.f};
    constexpr glm::vec3 p7 = {-1.f, -1.f, -1.f};
    constexpr glm::vec3 p8 = {-1.f, -1.f, 1.f};

    return {
        Quad(p1, p2, p3, p4), // RIGHT
        Quad(p5, p6, p7, p8), // LEFT
        Quad(p6, p5, p2, p1), // TOP
        Quad(p7, p8, p3, p4), // BOTTOM
        Quad(p6, p1, p4, p7), // FRONT
        Quad(p2, p5, p8, p3)  // BACK
    };
}

Cube::Cube(float width, float height, float depth, const std::shared_ptr<Material>& material)
    : Mesh(material)
    , m_quads(generate_default_quads())
{
    set_model(glm::scale(m_model, glm::vec3(width, height, depth)));

    std::array<Vertex, std::tuple_size<decltype(m_quads)>::value * Quad::VERTEX_COUNT> data;

    auto vertices_offset = 0;
    for (const Quad& quad : m_quads)
    {
        std::ranges::move(quad.get_vertices(), data.begin() + vertices_offset);
        vertices_offset += Quad::VERTEX_COUNT;
    }

    m_buffer = std::make_unique<Buffer>(data);
}

uint32_t Cube::get_triangle_count() const
{
    return m_quads.size() * Quad::TRIANGLE_COUNT;
}
