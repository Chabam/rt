#include "cube.h"

#include <object/quad.h>

Cube::Cube(uint8_t width, uint8_t height, uint8_t depth, const std::shared_ptr<Shader>& shader,
           const Material& material, const glm::mat4 model)
    : Mesh(getTrianglesFromQuads(generateQuads(width, height, depth)), shader, material, model)
    , m_quads(generateQuads(width, height, depth))
{
}

std::array<QuadPrimitive, 6> Cube::generateQuads(uint8_t width, uint8_t height, uint8_t depth)
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
		QuadPrimitive(p1, p2, p3, p4),
		QuadPrimitive(p6, p5, p2, p1),
		QuadPrimitive(p7, p8, p5, p6),
		QuadPrimitive(p4, p3, p8, p7),
		QuadPrimitive(p3, p2, p5, p8),
		QuadPrimitive(p1, p4, p7, p6)
	};
    // clang-format on
}

std::vector<TrianglePrimitive> Cube::getTrianglesFromQuads(std::array<QuadPrimitive, 6> quads)
{
    std::vector<TrianglePrimitive> triangles;
    for (const QuadPrimitive& quad : quads)
    {
        const auto& quadsTriangles = quad.m_triangles;
        triangles.insert(triangles.end(), quadsTriangles.begin(), quadsTriangles.end());
    }
    return triangles;
}
