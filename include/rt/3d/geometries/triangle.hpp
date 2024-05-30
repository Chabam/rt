#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include <rt/graphics/gl/vertex.hpp>

#include <array>
#include <glm/vec3.hpp>

class Triangle
{
  public:
    static constexpr auto VERTICE_COUNT = 3;

    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other);
    Triangle& operator=(const Triangle& other);

    std::array<glm::vec3, 3> m_p;
    glm::vec3 m_normal;

    std::array<Vertex, VERTICE_COUNT> getVertices() const;
};

#endif // RT_TRIANGLE_H