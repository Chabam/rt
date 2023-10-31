#pragma once
#include <object/trianglePrimitive.h>

#include <array>

class QuadPrimitive
{
  public:
    QuadPrimitive(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
    QuadPrimitive(const QuadPrimitive& other);
    QuadPrimitive& operator=(const QuadPrimitive& other);

    std::array<glm::vec3, 4> m_p;
    std::array<TrianglePrimitive, 2> m_triangles;
};