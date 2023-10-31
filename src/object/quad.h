#pragma once
#include <object/mesh.h>
#include <object/triangle.h>

#include <array>

class Quad : public Mesh
{
  public:
    Quad(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 &p4);
    Quad(const Quad &other);
    Quad &operator=(const Quad &other);

	std::array<glm::vec3, 4> m_p;
};