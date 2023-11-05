#pragma once
#include <object/triangle.h>

#include <array>

class Quad
{
  public:
    Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
    Quad(const Quad& other);
    Quad& operator=(const Quad& other);
    void swap(Quad& other) noexcept;

    operator std::vector<VerticeBufferData>() const;

    std::array<glm::vec3, 4> m_p;
    std::array<Triangle, 2> m_triangleParts;
};