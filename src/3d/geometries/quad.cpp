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

std::array<VerticeBufferData, Quad::VERTICE_COUNT> Quad::getVerticeBufferData() const
{
    std::array<VerticeBufferData, VERTICE_COUNT> verticeData;

    auto verticeOffset = 0;
    for (const auto& triangle : m_triangleParts)
    {
        std::ranges::move(triangle.getVerticeBufferData(), verticeData.begin() + verticeOffset);
        verticeOffset += Triangle::VERTICE_COUNT;
    }

    return verticeData;
}