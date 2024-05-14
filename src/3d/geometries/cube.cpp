#include <rt/3d/geometries/cube.hpp>

#include <cassert>

Cube::Cube(unsigned int width, unsigned int height, unsigned int depth, const std::shared_ptr<Shader>& shader,
           const Material& material, const glm::mat4 model)
    : Mesh(shader, material)
    , m_quadParts(generateQuads(width, height, depth))
{
    std::vector<Triangle> triangles;
    for (const Quad& quad : m_quadParts)
    {
        assert(quad.m_triangleParts[0].m_normal == quad.m_triangleParts[1].m_normal); // "Normal not set correctly"
        triangles.insert(triangles.end(), quad.m_triangleParts.begin(), quad.m_triangleParts.end());
    }
    setTriangles(triangles);
}

std::array<Quad, 6> Cube::generateQuads(unsigned int width, unsigned int height, unsigned int depth)
{
    const float halfWidth = width / 2.f;
    const float halfHeight = height / 2.f;
    const float halfDepth = depth / 2.f;

    const glm::vec3 p1 = {halfWidth, halfHeight, -halfDepth};
    const glm::vec3 p2 = {halfWidth, halfHeight, halfDepth};
    const glm::vec3 p3 = {halfWidth, -halfHeight, halfDepth};
    const glm::vec3 p4 = {halfWidth, -halfHeight, -halfDepth};
    const glm::vec3 p5 = {-halfWidth, halfHeight, halfDepth};
    const glm::vec3 p6 = {-halfWidth, halfHeight, -halfDepth};
    const glm::vec3 p7 = {-halfWidth, -halfHeight, -halfDepth};
    const glm::vec3 p8 = {-halfWidth, -halfHeight, halfDepth};

    return {
        Quad(p1, p2, p3, p4), // RIGHT
        Quad(p5, p6, p7, p8), // LEFT
        Quad(p6, p5, p2, p1), // TOP
        Quad(p7, p8, p3, p4), // BOTTOM
        Quad(p6, p1, p4, p7), // FRONT
        Quad(p2, p5, p8, p3)  // BACK
    };
}
