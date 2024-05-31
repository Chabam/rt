#include <rt/graphics/primitives/quad.hpp>

#include <algorithm>
#include <ranges>

Quad::Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
    : m_p{p1, p2, p3, p4}
    , m_triangles({Triangle(p1, p2, p3), Triangle(p3, p4, p1)})
{
}

Quad::Quad(const Quad& other)
    : m_p(other.m_p)
    , m_triangles(other.m_triangles)
{
}

Quad& Quad::operator=(const Quad& other)
{
    m_p = other.m_p;
    m_triangles = other.m_triangles;

    return *this;
}

std::array<Vertex, Quad::VERTEX_COUNT> Quad::get_vertices() const
{
    std::array<Vertex, VERTEX_COUNT> verticeData;

    auto verticeOffset = 0;
    for (const auto& triangle : m_triangles)
    {
        std::ranges::move(triangle.get_vertices(), verticeData.begin() + verticeOffset);
        verticeOffset += Triangle::VERTEX_COUNT;
    }

    return verticeData;
}