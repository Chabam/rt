#pragma once
#include <object/mesh.h>
#include <object/quad.h>
#include <array>

class Cube : public Mesh
{
  public:
    Cube(const Material& material = Material());

    const glm::vec3 p1 = {1, -1, 1};
    const glm::vec3 p2 = {1, 1, 1};
    const glm::vec3 p4 = {1, -1, -1};
    const glm::vec3 p7 = {-1, -1, -1};
    const glm::vec3 p3 = {1, 1, -1};
    const glm::vec3 p5 = {-1, 1, 1};
    const glm::vec3 p6 = {-1, -1, 1};
    const glm::vec3 p8 = {-1, 1, -1};

    // clang-format off
	std::array<Quad, 6> m_quads = {
		Quad(p1, p2, p3, p4),
		Quad(p6, p5, p2, p1),
		Quad(p7, p8, p5, p6),
		Quad(p4, p3, p8, p7),
		Quad(p3, p2, p5, p8),
		Quad(p1, p4, p7, p6)
	};
    // clang-format on
};