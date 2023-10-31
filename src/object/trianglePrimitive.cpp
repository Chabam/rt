#include "trianglePrimitive.h"

TrianglePrimitive::TrianglePrimitive(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
    : m_p({p1, p2, p3})
{
}

TrianglePrimitive::TrianglePrimitive(const TrianglePrimitive& other)
    : m_p(other.m_p)
{
}

TrianglePrimitive::TrianglePrimitive(const std::array<glm::vec3, 3>& other)
    : m_p(other)
{
}

TrianglePrimitive& TrianglePrimitive::operator=(const TrianglePrimitive& other)
{
    m_p = other.m_p;

    return *this;
}