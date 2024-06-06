#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

#include <rt/graphics/primitives/quad.hpp>

#include <array>
#include <utility>

namespace rt
{

constexpr std::array<glm::vec2, Quad::POINT_COUNT> default_uvs = {glm::vec2{0.f, 1.f}, glm::vec2{1.f, 1.f},
                                                                  glm::vec2{1.f, 0.f}, glm::vec2{0.f, 0.f}};

Quad::Quad(const std::array<glm::vec3, POINT_COUNT>& pts)
    : m_vertices{}
    , m_indices{0, 1, 2, 2, 3, 0}
    , m_normal{Triangle{{pts[0], pts[1], pts[2]}}.m_normal}
{
    for (unsigned int i = 0; i < POINT_COUNT; ++i)
    {
        m_vertices[i] = Vertex{pts[i], m_normal, default_uvs[i]};
    }
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

} // namespace rt