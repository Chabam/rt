#ifndef RT_QUAD_H
#define RT_QUAD_H

#include <rt/3d/geometries/triangle.hpp>

#include <array>

class Quad
{
  public:
    static constexpr auto TRIANGLE_COUNT = 2;
    static constexpr auto VERTICE_COUNT = Triangle::VERTICE_COUNT * TRIANGLE_COUNT;
    Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
    Quad(const Quad& other);
    Quad& operator=(const Quad& other);

    std::array<Vertex, VERTICE_COUNT> getVertices() const;

    std::array<glm::vec3, 4> m_p;
    std::array<Triangle, TRIANGLE_COUNT> m_triangleParts;
};

#endif // RT_QUAD_H