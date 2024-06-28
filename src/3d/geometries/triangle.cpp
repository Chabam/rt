#include <rt/3d/geometries/triangle.hpp>
#include <rt/graphics/gl/vertex.hpp>

#include <algorithm>
#include <array>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <utility>

namespace rt
{

Triangle::Triangle(const std::array<glm::vec3, POINT_COUNT>& pts)
    : m_vertices{}
    , m_indices{0, 1, 2}
    , m_normal(glm::normalize(glm::cross(pts[2] - pts[1], pts[0] - pts[1])))
{
    std::ranges::transform(pts, m_vertices.begin(), [this](const glm::vec3& point) { return Vertex{point, m_normal}; });
}

Triangle::Triangle(const Triangle& other)
    : m_vertices{other.m_vertices}
    , m_indices{other.m_indices}
    , m_normal(other.m_normal)
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
    m_vertices = other.m_vertices;
    m_indices = other.m_indices;
    m_normal = other.m_normal;

    return *this;
}

Triangle::Triangle(Triangle&& other)
    : m_vertices(std::move(other.m_vertices))
    , m_indices(std::move(other.m_indices))
    , m_normal(std::move(other.m_normal))
{
}

Triangle& Triangle::operator=(Triangle&& other)
{
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    m_normal = std::move(other.m_normal);

    return *this;
}

std::span<const Vertex> Triangle::get_vertices() const
{
    return m_vertices;
}

std::span<const unsigned int> Triangle::get_indices() const
{
    return m_indices;
}

const glm::vec3& Triangle::get_normal() const
{
    return m_normal;
}

} // namespace rt