#include "glm/ext/vector_float3.hpp"
#include "rt/3d/mesh.hpp"

#include <rt/3d/geometries/plane.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <memory>


namespace rt
{

constexpr glm::vec3 p1 = {-1.f, 1.f, 0.f};
constexpr glm::vec3 p2 = {1.f, 1.f, 0.f};
constexpr glm::vec3 p3 = {1.f, -1.f, 0.f};
constexpr glm::vec3 p4 = {-1.f, -1.f, 0.f};

Plane::Plane(float width, float height, const std::shared_ptr<Material>& material,
             const std::shared_ptr<Texture>& texture)
    : Mesh(material, texture)
    , m_quad{{p1, p2, p3, p4}}
{
    m_model *= glm::scale(m_model, glm::vec3(width, height, 1.f));

    m_buffer = std::make_unique<Buffer>(m_quad.m_vertices, m_quad.m_indices);
}

unsigned int Plane::get_triangle_count() const
{
    return Quad::TRIANGLE_COUNT;
}

} // namespace rt