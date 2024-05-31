#ifndef RT_QUAD_H
#define RT_QUAD_H

#include <rt/graphics/primitives/triangle.hpp>

#include <array>

class Quad
{
  public:
    static constexpr auto TRIANGLE_COUNT = 2;
    static constexpr auto VERTEX_COUNT = Triangle::VERTEX_COUNT * TRIANGLE_COUNT;
    Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
    Quad(const Quad& other);
    Quad& operator=(const Quad& other);

    std::array<Vertex, VERTEX_COUNT> get_vertices() const;

    std::array<glm::vec3, 4> m_p;
    std::array<Triangle, TRIANGLE_COUNT> m_triangles;
};

#endif // RT_QUAD_H