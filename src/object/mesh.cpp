#include "mesh.h"

#include <object/geometries/triangle.h>
#include <algorithm>
#include <utils/logger.h>

Mesh::Mesh(const std::shared_ptr<Shader>& shader, const Material& material)
    : Object3d(shader, material)
    , m_triangles()
{
}

void Mesh::setTriangles(const std::vector<Triangle>& triangles)
{
    m_triangles = triangles;
    std::vector<VerticeBufferData> vertices;
    vertices.reserve(triangles.size() * std::tuple_size<decltype(Triangle::m_p)>::value);

    for (const Triangle& triangle : m_triangles)
    {
        std::vector<VerticeBufferData> triangleVec{triangle};
        vertices.insert(vertices.end(), triangleVec.begin(), triangleVec.end());
    }
    
    m_buffer = std::make_unique<Buffer>(vertices);
}

uint32_t Mesh::getTriangleCount() const
{
    return m_triangles.size();
}