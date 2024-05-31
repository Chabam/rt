#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include <rt/graphics/primitives/vertex.hpp>

#include <array>
#include <glm/vec3.hpp>

class Triangle
{
  public:
    static constexpr auto VERTEX_COUNT = 3;

    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other);
    Triangle& operator=(const Triangle& other);

    std::array<glm::vec3, 3> m_p;
    glm::vec3 m_normal;

    std::array<Vertex, VERTEX_COUNT> get_vertices() const;
};

#endif // RT_TRIANGLE_H