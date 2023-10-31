#include "quadPrimitive.h"

QuadPrimitive::QuadPrimitive(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
    : m_p{p1, p2, p3, p4}
    , m_triangles({TrianglePrimitive(p1, p2, p3), TrianglePrimitive(p1, p3, p4)})
{
}

QuadPrimitive::QuadPrimitive(const QuadPrimitive& other)
    : m_p(other.m_p)
    , m_triangles(other.m_triangles)
{
}

QuadPrimitive& QuadPrimitive::operator=(const QuadPrimitive& other)
{
    m_p = other.m_p;
    m_triangles = other.m_triangles;

    return *this;
}