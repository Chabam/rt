#include <rt/3d/geometries/triangle.hpp>
#include <rt/graphics/gl/vertex.hpp>

#include <array>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <utility>

namespace rt
{

Triangle::Triangle(const std::array<glm::vec3, POINT_COUNT>& pts, const std::array<glm::vec2, Triangle::POINT_COUNT>& uvs)
    : m_vertices{}
    , m_indices{0, 1, 2}
    , m_normal{glm::normalize(glm::cross(pts[2] - pts[1], pts[0] - pts[1]))}
    , m_tangent{}
    , m_bi_tangent{}
{
    glm::vec3 edge_1 = pts[1] - pts[0];
    glm::vec3 edge_2 = pts[2] - pts[0];
    glm::vec2 delta_uv_1 = uvs[1] - uvs[0];
    glm::vec2 delta_uv_2 = uvs[2] - uvs[1];

    float f = 1.0f / (delta_uv_1.x * delta_uv_2.y - delta_uv_2.x * delta_uv_1.y);

    m_tangent.x = f * (delta_uv_2.y * edge_1.x - delta_uv_1.y * edge_2.x);
    m_tangent.y = f * (delta_uv_2.y * edge_1.y - delta_uv_1.y * edge_2.y);
    m_tangent.z = f * (delta_uv_2.y * edge_1.z - delta_uv_1.y * edge_2.z);

    m_bi_tangent.x = f * (-delta_uv_2.x * edge_1.x + delta_uv_1.x * edge_2.x);
    m_bi_tangent.y = f * (-delta_uv_2.x * edge_1.y + delta_uv_1.x * edge_2.y);
    m_bi_tangent.z = f * (-delta_uv_2.x * edge_1.z + delta_uv_1.x * edge_2.z);

    for (unsigned int i = 0; i < POINT_COUNT; ++i)
    {
        m_vertices[i] = Vertex{pts[i], m_normal, uvs[i], m_tangent, m_bi_tangent};
    }
}

Triangle::Triangle(const Triangle& other)
    : m_vertices{other.m_vertices}
    , m_indices{other.m_indices}
    , m_normal(other.m_normal)
    , m_tangent(other.m_tangent)
    , m_bi_tangent(other.m_bi_tangent)
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
    m_vertices = other.m_vertices;
    m_indices = other.m_indices;
    m_normal = other.m_normal;
    m_tangent = other.m_tangent;
    m_bi_tangent = other.m_bi_tangent;

    return *this;
}

Triangle::Triangle(Triangle&& other)
    : m_vertices(std::move(other.m_vertices))
    , m_indices(std::move(other.m_indices))
    , m_normal(std::move(other.m_normal))
    , m_tangent(std::move(other.m_tangent))
    , m_bi_tangent(std::move(other.m_bi_tangent))
{
}

Triangle& Triangle::operator=(Triangle&& other)
{
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    m_normal = std::move(other.m_normal);
    m_tangent = std::move(other.m_tangent);
    m_bi_tangent = std::move(other.m_bi_tangent);

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

const glm::vec3& Triangle::get_tangent() const
{
    return m_tangent;
}

const glm::vec3& Triangle::get_bi_tangent() const
{
    return m_bi_tangent;
}


} // namespace rt
