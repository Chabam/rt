#include "triangle.h"

Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
    : m_p({p1, p2, p3})
{
}

Triangle::Triangle(const Triangle& other)
    : m_p(other.m_p)
{
}

Triangle::Triangle(const std::array<glm::vec3, 3>& other)
    : m_p(other)
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
    m_p = other.m_p;

    return *this;
}

Triangle::operator std::vector<glm::vec3, std::allocator<glm::vec3>>() const
{
    return {m_p.begin(), m_p.end()};
}