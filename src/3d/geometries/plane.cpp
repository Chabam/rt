#include <rt/3d/geometries/plane.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

constexpr glm::vec3 p1 = {-1.f, 1.f, 0.f};
constexpr glm::vec3 p2 = {1.f, 1.f, 0.f};
constexpr glm::vec3 p3 = {1.f, -1.f, 0.f};
constexpr glm::vec3 p4 = {-1.f, -1.f, 0.f};

Plane::Plane(float width, float height, const std::shared_ptr<Material>& material)
    : Mesh(material)
    , m_quad(p1, p2, p3, p4)
{
    m_model *= glm::scale(m_model, glm::vec3(width, height, 1.f));

    m_buffer = std::make_unique<Buffer>(m_quad.get_vertices());
}

uint32_t Plane::get_triangle_count() const
{
    return Quad::TRIANGLE_COUNT;
}
