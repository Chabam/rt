#include <rt/3d/geometries/quad.hpp>

#include <algorithm>
#include <ranges>

Quad::Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
    : m_p{p1, p2, p3, p4}
    , m_triangleParts({Triangle(p1, p2, p3), Triangle(p3, p4, p1)})
{
}

Quad::Quad(const Quad& other)
    : m_p(other.m_p)
    , m_triangleParts(other.m_triangleParts)
{
}

Quad& Quad::operator=(const Quad& other)
{
    m_p = other.m_p;
    m_triangleParts = other.m_triangleParts;

    return *this;
}

Quad::operator std::vector<VerticeBufferData>() const
{
    std::vector<VerticeBufferData> result{m_triangleParts[0]};
    const std::vector<VerticeBufferData> vec2{m_triangleParts[1]};
    result.insert(result.end(), vec2.begin(), vec2.end());

    return result;
}