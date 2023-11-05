#include "mesh.h"

#include <algorithm>
#include <utils/logger.h>

Mesh::Mesh(const std::vector<TrianglePrimitive>& triangles, const std::shared_ptr<Shader>& shader, const Material& material,
           const glm::mat4 model)
    : Object3d(Mesh::getVertices(triangles), shader, material, model)
    , m_triangles(triangles)
{
}

std::vector<glm::vec3> Mesh::getVertices(const std::vector<TrianglePrimitive>& triangles)
{
    std::vector<glm::vec3> vertices;
    for (const TrianglePrimitive& triangle : triangles)
    {
        vertices.insert(vertices.begin(), {triangle.m_p[0], triangle.m_p[1], triangle.m_p[2]});
    }
    return vertices;
}

uint32_t Mesh::getTriangleCount() const
{
    return m_triangles.size();
}

const std::vector<TrianglePrimitive>& Mesh::getTriangles() const
{
    return m_triangles;
}
