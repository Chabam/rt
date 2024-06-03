#include <rt/graphics/primitives/quad.hpp>

#include <algorithm>
#include <glm/geometric.hpp>
#include <ranges>

Quad::Quad(const std::array<glm::vec3, POINT_COUNT>& pts)
    : m_vertices{}
    , m_indices{0, 1, 2, 2, 3, 0}
    , m_normal{Triangle{{pts[0], pts[1], pts[2]}}.m_normal}
{
    std::ranges::transform(pts, m_vertices.begin(), [this](const glm::vec3& point) { return Vertex{point, m_normal}; });
}

Quad::Quad(const Quad& other)
    : m_vertices(other.m_vertices)
    , m_indices(other.m_indices)
    , m_normal(other.m_normal)
{
}

Quad& Quad::operator=(const Quad& other)
{
    m_vertices = other.m_vertices;
    m_indices = other.m_indices;
    m_normal = other.m_normal;

    return *this;
}

Quad::Quad(Quad&& other)
    : m_vertices(std::move(other.m_vertices))
    , m_indices(std::move(other.m_indices))
    , m_normal(std::move(other.m_normal))
{
}

Quad& Quad::operator=(Quad&& other)
{
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    m_normal = std::move(other.m_normal);

    return *this;
}