#include <rt/graphics/primitives/triangle.hpp>

#include <algorithm>
#include <glm/geometric.hpp>

Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
    : m_p({p1, p2, p3})
    , m_normal(glm::normalize(glm::cross(p3 - p2, p1 - p2)))
{
}

Triangle::Triangle(const Triangle& other)
    : m_p(other.m_p)
    , m_normal(other.m_normal)
{
}

Triangle::Triangle(Triangle&& other)
    : m_p(std::move(other.m_p))
    , m_normal(std::move(other.m_normal))
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
    m_p = other.m_p;

    return *this;
}

std::array<Vertex, Triangle::VERTEX_COUNT> Triangle::get_vertices() const
{
    std::array<Vertex, 3> vertices;

    std::ranges::transform(m_p, vertices.begin(), [this](const glm::vec3& point) { return Vertex{point, m_normal}; });

    return vertices;
}