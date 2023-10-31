#pragma once
#include <glm/vec3.hpp>
#include <array>

class Triangle
{
  public:
    Triangle(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3);
    Triangle(const Triangle &other);
    Triangle(const std::array<glm::vec3, 3> &other);
    Triangle& operator=(const Triangle &other);

    std::array<glm::vec3, 3> m_p;
};