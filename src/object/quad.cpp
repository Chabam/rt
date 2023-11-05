#include "quad.h"

#include <algorithm>
#include <ranges>

Quad::Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
    : m_p{p1, p2, p3, p4}
    , m_triangleParts({Triangle(p1, p2, p3), Triangle(p1, p3, p4)})
{
}

Quad::Quad(const Quad& other)
    : m_p(other.m_p)
    , m_triangleParts(other.m_triangleParts)
{
}

Quad& Quad::operator=(const Quad& other)
{
    Quad(other).swap(*this);

    return *this;
}

void Quad::swap(Quad& other) noexcept
{
    std::swap(other.m_p, m_p);
    std::swap(other.m_triangleParts, m_triangleParts);
}

Quad::operator std::vector<glm::vec3, std::allocator<glm::vec3>>() const
{
    std::vector<glm::vec3> result{m_triangleParts[0]};
    const std::vector<glm::vec3> vec2{m_triangleParts[1]};
    result.insert(result.end(), vec2.begin(), vec2.end());

    return result;
}