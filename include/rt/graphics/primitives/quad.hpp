#ifndef RT_QUAD_H
#define RT_QUAD_H

#include "glm/ext/vector_float3.hpp"
#include "rt/graphics/primitives/vertex.hpp"
#include <rt/graphics/primitives/triangle.hpp>

#include <array>

namespace rt
{

struct Quad
{
    static constexpr auto POINT_COUNT = 4;
    static constexpr auto TRIANGLE_COUNT = 2;
    static constexpr auto VERTEX_COUNT = Triangle::VERTEX_COUNT * TRIANGLE_COUNT;

    Quad() = default;
    Quad(const std::array<glm::vec3, POINT_COUNT>& pts);

    Quad(const Quad& other);
    Quad& operator=(const Quad& other);

    Quad(Quad&& other);
    Quad& operator=(Quad&& other);

    std::array<Vertex, POINT_COUNT> m_vertices;
    std::array<unsigned short, VERTEX_COUNT> m_indices;
    glm::vec3 m_normal;
};

} // namespace rt

#endif // RT_QUAD_H