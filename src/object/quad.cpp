#include "quad.h"

Quad::Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4,
           const std::shared_ptr<Shader>& shader, const Material& material, const glm::mat4 model)
    : QuadPrimitive(p1, p2, p3, p4)
    , Mesh({QuadPrimitive::m_triangles[0], QuadPrimitive::m_triangles[1]}, shader, material, model)
{
}

Quad::Quad(const Quad& other)
    : QuadPrimitive(other)
    , Mesh(other.getTriangles(), other.m_shader, other.m_material, other.m_model)
{
}

Quad& Quad::operator=(const Quad& other)
{
    m_p = other.m_p;

    return *this;
}