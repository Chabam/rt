#include <rt/3d/geometries/cube.hpp>

#include <cassert>
#include <glm/ext/matrix_transform.hpp>

std::array<Quad, 6> generateDefaultQuads()
{
    constexpr glm::vec3 p1 = {1.f, 1.f, -1.f};
    constexpr glm::vec3 p2 = {1.f, 1.f, 1.f};
    constexpr glm::vec3 p3 = {1.f, -1.f, 1.f};
    constexpr glm::vec3 p4 = {1.f, -1.f, -1.f};
    constexpr glm::vec3 p5 = {-1.f, 1.f, 1.f};
    constexpr glm::vec3 p6 = {-1.f, 1.f, -1.f};
    constexpr glm::vec3 p7 = {-1.f, -1.f, -1.f};
    constexpr glm::vec3 p8 = {-1.f, -1.f, 1.f};

    return {
        Quad(p1, p2, p3, p4), // RIGHT
        Quad(p5, p6, p7, p8), // LEFT
        Quad(p6, p5, p2, p1), // TOP
        Quad(p7, p8, p3, p4), // BOTTOM
        Quad(p6, p1, p4, p7), // FRONT
        Quad(p2, p5, p8, p3)  // BACK
    };
}

Cube::Cube(float width, float height, float depth, const std::shared_ptr<Shader>& shader, const Material& material,
           const glm::mat4 model)
    : Mesh(shader, material)
    , m_quadParts(generateDefaultQuads())
{
    std::vector<Triangle> triangles;
    triangles.reserve(m_quadParts.size() * 2);
    for (const Quad& quad : m_quadParts)
    {
        assert(quad.m_triangleParts[0].m_normal == quad.m_triangleParts[1].m_normal && "Normals not set correctly!");
        triangles.insert(triangles.end(), quad.m_triangleParts.begin(), quad.m_triangleParts.end());
    }
    setTriangles(triangles);
    m_model = glm::scale(m_model, glm::vec3(width, height, depth));
}
