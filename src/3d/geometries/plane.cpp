#include <rt/3d/geometries/plane.hpp>

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

constexpr glm::vec3 p1 = {-1.f, 1.f, 0.f};
constexpr glm::vec3 p2 = {1.f, 1.f, 0.f};
constexpr glm::vec3 p3 = {1.f, -1.f, 0.f};
constexpr glm::vec3 p4 = {-1.f, -1.f, 0.f};

Plane::Plane(float width, float height, const std::shared_ptr<Shader>& shader, const Material& material,
             const glm::mat4 model)
    : Mesh(shader, material)
    , m_quad(p1, p2, p3, p4)
{
    setTriangles({m_quad.m_triangleParts.begin(), m_quad.m_triangleParts.end()});
    m_model *= glm::scale(m_model, glm::vec3(width, height, 1.f));
}

Plane::Plane(const Plane& other)
    : m_quad(other.m_quad)
    , Mesh(other.m_shader, other.m_material)
{
    setTriangles(other.m_triangles);
}

Plane& Plane::operator=(const Plane& other)
{
    m_quad = other.m_quad;

    return *this;
}