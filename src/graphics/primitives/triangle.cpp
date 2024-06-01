#include <rt/graphics/primitives/triangle.hpp>

#include <algorithm>
#include <glm/geometric.hpp>

Triangle::Triangle(const std::array<glm::vec3, POINT_COUNT>& pts)
    : m_vertices{}
    , m_indices{0, 1, 2}
    , m_normal(glm::normalize(glm::cross(pts[2] - pts[1], pts[0] - pts[1])))
{
    std::ranges::transform(pts, m_vertices.begin(), [this](const glm::vec3& point) { return Vertex{point, m_normal}; });
}

Triangle::Triangle(const std::array<std::tuple<glm::vec3, unsigned short>, POINT_COUNT>& idx_pts)
    : m_vertices{}
    , m_indices{std::get<1>(idx_pts[0]), std::get<1>(idx_pts[1]), std::get<1>(idx_pts[2])}
    , m_normal(glm::normalize(glm::cross(std::get<0>(idx_pts[2]) - std::get<0>(idx_pts[1]),
                                         std::get<0>(idx_pts[0]) - std::get<0>(idx_pts[1]))))
{
    std::ranges::transform(idx_pts, m_vertices.begin(),
                           [this](const auto& point) { return Vertex{std::get<0>(point), m_normal}; });
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
    other.m_vertices = {};
    other.m_indices = {};
    other.m_normal = {};
}

Triangle& Triangle::operator=(Triangle&& other)
{
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    m_normal = std::move(other.m_normal);

    other.m_normal = {};
    other.m_indices = {};
    other.m_vertices = {};

    return *this;
}