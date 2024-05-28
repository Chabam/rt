#include <rt/3d/geometries/cube.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <algorithm>
#include <cassert>
#include <glm/ext/matrix_transform.hpp>
#include <iterator>


std::array<Quad, 6> generateDefaultQuads()
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

Cube::Cube(float width, float height, float depth, const Material& material)
    : Mesh(material)
    , m_quadParts(generateDefaultQuads())
{
    setModel(glm::scale(m_model, glm::vec3(width, height, depth)));

    std::array<VerticeBufferData, std::tuple_size<decltype(m_quadParts)>::value * Quad::VERTICE_COUNT> data;

    auto verticeOffset = 0;
    for (const Quad& quad : m_quadParts)
    {
        std::ranges::move(quad.getVerticeBufferData(), data.begin() + verticeOffset);
        verticeOffset += Quad::VERTICE_COUNT;
    }

    m_buffer = std::make_unique<Buffer>(data);
}

uint32_t Cube::getTriangleCount() const
{
    return m_quadParts.size() * Quad::TRIANGLE_COUNT;
}
