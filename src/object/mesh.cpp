#include "object/mesh.h"
#include <algorithm>
#include "logger/logger.h"
#include "glm/gtx/string_cast.hpp"

Mesh::Mesh(const std::vector<Triangle> &triangles, const Material &material)
    : m_triangles(triangles), m_model(1.f), m_material(material)
{
}

Mesh::Mesh(const Mesh &other) : m_triangles(other.m_triangles), m_model(other.m_model), m_material(other.m_material)
{
}

Mesh::Mesh() : m_triangles(), m_model(1.f), m_material()
{
}

Mesh &Mesh::operator=(const Mesh &other)
{
    m_triangles = other.m_triangles;
    m_model = other.m_model;
    m_material = other.m_material;

    return *this;
}

std::vector<Vertice> Mesh::getVertices() const
{
    std::vector<Vertice> vertices;
    for (const Triangle &triangle : m_triangles)
    {
        vertices.insert(vertices.begin(), {triangle.m_p[0], triangle.m_p[1], triangle.m_p[2]});
    }
    return vertices;
}

uint32_t Mesh::getTriangleCount() const
{
    return m_triangles.size();
}

const glm::mat4 &Mesh::getModel() const
{
    return m_model;
}

void Mesh::applyTransformation(const glm::mat4 &trans)
{
    m_model = m_model * trans;
}

const std::vector<Triangle> &Mesh::getTriangles() const
{
    return m_triangles;
}

const Material &Mesh::getMaterial() const
{
    return m_material;
}