#include <rt/3d/geometries/plane.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>

namespace rt
{

Plane::Plane(float width, float height)
    : m_quad{}
{
    const glm::vec3 scale_vector{width, height, 1.f};
    const glm::vec3 p1 = scale_vector * glm::vec3{-1.f, 1.f, 0.f};
    const glm::vec3 p2 = scale_vector * glm::vec3{1.f, 1.f, 0.f};
    const glm::vec3 p3 = scale_vector * glm::vec3{1.f, -1.f, 0.f};
    const glm::vec3 p4 = scale_vector * glm::vec3{-1.f, -1.f, 0.f};

    m_quad = {{p1, p2, p3, p4}};
}

std::span<const Vertex> Plane::get_vertices() const
{
    return m_quad.get_vertices();
}

std::span<const unsigned short> Plane::get_indices() const
{
    return m_quad.get_indices();
}

} // namespace rt