#include "quadMesh.h"

#include <algorithm>

QuadMesh::QuadMesh(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4,
                   const std::shared_ptr<Shader>& shader, const Material& material, const glm::mat4 model)
    : Quad(p1, p2, p3, p4)
    , Mesh(shader, material)
{
    setTriangles({Quad::m_triangleParts.begin(), Quad::m_triangleParts.end()});
}

QuadMesh::QuadMesh(const QuadMesh& other)
    : Quad(other)
    , Mesh(other.m_shader, other.m_material)
{
    setTriangles(other.getTriangles());
}

QuadMesh& QuadMesh::operator=(const QuadMesh& other)
{
    m_p = other.m_p;

    return *this;
}

void QuadMesh::swap(QuadMesh& other)
{

}