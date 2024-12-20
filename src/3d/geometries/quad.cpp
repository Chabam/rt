
#include <rt/3d/geometries/quad.hpp>

namespace rt
{

constexpr std::array<glm::vec2, Quad::POINT_COUNT> default_uvs = {glm::vec2{0.f, 1.f}, glm::vec2{1.f, 1.f},
                                                                  glm::vec2{1.f, 0.f}, glm::vec2{0.f, 0.f}};

Quad::Quad(const std::array<glm::vec3, POINT_COUNT>& pts)
    : m_vertices{}
    , m_indices{0, 1, 2, 2, 3, 0}
    , m_normal{}
    , m_tangent{}
    , m_bi_tangent{}
{
    Triangle tmp_triangle{{pts[0], pts[1], pts[2]}};
    m_normal = tmp_triangle.get_normal();
    m_tangent = tmp_triangle.get_tangent();
    m_bi_tangent = tmp_triangle.get_bi_tangent();

    for (unsigned int i = 0; i < POINT_COUNT; ++i)
    {
        m_vertices[i] = Vertex{pts[i], m_normal, default_uvs[i], m_tangent, m_bi_tangent};
    }
}

Quad::Quad(const Quad& other)
    : m_vertices{other.m_vertices}
    , m_indices{other.m_indices}
    , m_normal{other.m_normal}
    , m_tangent{other.m_tangent}
    , m_bi_tangent{other.m_bi_tangent}
{
}

Quad& Quad::operator=(const Quad& other)
{
    m_vertices = other.m_vertices;
    m_indices = other.m_indices;
    m_normal = other.m_normal;
    m_tangent = other.m_tangent;
    m_bi_tangent = other.m_bi_tangent;

    return *this;
}

Quad::Quad(Quad&& other)
    : m_vertices{std::move(other.m_vertices)}
    , m_indices{std::move(other.m_indices)}
    , m_normal{std::move(other.m_normal)}
    , m_tangent{std::move(other.m_tangent)}
    , m_bi_tangent{std::move(other.m_bi_tangent)}
{
}

Quad& Quad::operator=(Quad&& other)
{
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    m_normal = std::move(other.m_normal);
    m_tangent = std::move(other.m_tangent);
    m_bi_tangent = std::move(other.m_bi_tangent);

    return *this;
}

std::span<const Vertex> Quad::get_vertices() const
{
    return m_vertices;
}

std::span<const unsigned int> Quad::get_indices() const
{
    return m_indices;
}

} // namespace rt