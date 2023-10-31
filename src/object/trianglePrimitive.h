#pragma once
#include <glm/vec3.hpp>
#include <array>

class TrianglePrimitive
{
  public:
    TrianglePrimitive(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3);
    TrianglePrimitive(const TrianglePrimitive &other);
    TrianglePrimitive(const std::array<glm::vec3, 3> &other);
    TrianglePrimitive& operator=(const TrianglePrimitive &other);

    std::array<glm::vec3, 3> m_p;
};