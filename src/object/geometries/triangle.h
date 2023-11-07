#pragma once
#include <array>
#include <glContext/verticeBufferData.h>
#include <glm/vec3.hpp>
#include <vector>

class Triangle
{
  public:
    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);

    std::array<glm::vec3, 3> m_p;
    glm::vec3 m_normal;

    operator std::vector<VerticeBufferData>() const;
};