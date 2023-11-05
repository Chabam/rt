#include "triangle.h"
#include <glm/geometric.hpp>

Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
    : m_p({p1, p2, p3})
    , m_normal(glm::normalize(glm::cross(p1 - p2, p3 - p2)))
{
}

Triangle::Triangle(const Triangle& other)
    : m_p(other.m_p)
    , m_normal(other.m_normal)
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
    m_p = other.m_p;

    return *this;
}

Triangle::operator std::vector<VerticeBufferData>() const
{
    std::vector<VerticeBufferData> verticeData;
    
    verticeData.reserve(std::tuple_size<decltype(m_p)>::value);
    for (const auto& point : m_p)
    {
        verticeData.emplace_back(point, m_normal);
    }

    return verticeData;
}