#include "cube.h"

Cube::Cube(unsigned int width, unsigned int height, unsigned int depth, const std::shared_ptr<Shader>& shader,
           const Material& material, const glm::mat4 model)
    : Mesh(shader, material)
    , m_quads(generateQuads(width, height, depth))
{
    std::vector<Triangle> triangles;
    for (const Quad& quad : m_quads)
    {
        triangles.insert(triangles.end(), quad.m_triangleParts.begin(), quad.m_triangleParts.end());
    }
    setTriangles(triangles);
}

std::array<Quad, 6> Cube::generateQuads(unsigned int width, unsigned int height, unsigned int depth)
{
    const float halfWidth = width / 2.f;
    const float halfHeight = height / 2.f;
    const float halfDepth = depth / 2.f;
    const glm::vec3 p1 = {halfWidth, -halfHeight, halfDepth};
    const glm::vec3 p2 = {halfWidth, halfHeight, halfDepth};
    const glm::vec3 p4 = {halfWidth, -halfHeight, -halfDepth};
    const glm::vec3 p7 = {-halfWidth, -halfHeight, -halfDepth};
    const glm::vec3 p3 = {halfWidth, halfHeight, -halfDepth};
    const glm::vec3 p5 = {-halfWidth, halfHeight, halfDepth};
    const glm::vec3 p6 = {-halfWidth, -halfHeight, halfDepth};
    const glm::vec3 p8 = {-halfWidth, halfHeight, -halfDepth};

    // clang-format off
    return {
		Quad(p1, p2, p3, p4),
		Quad(p6, p5, p2, p1),
		Quad(p7, p8, p5, p6),
		Quad(p4, p3, p8, p7),
		Quad(p3, p2, p5, p8),
		Quad(p1, p4, p7, p6)
	};
    // clang-format on
}
