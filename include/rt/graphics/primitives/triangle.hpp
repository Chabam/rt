#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include "glm/ext/vector_float3.hpp"
#include <rt/graphics/primitives/vertex.hpp>

#include <array>

namespace rt
{

struct Triangle
{
    static constexpr auto POINT_COUNT = 3;
    static constexpr auto VERTEX_COUNT = POINT_COUNT;

    Triangle(const std::array<glm::vec3, POINT_COUNT>& pts);

    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);

    Triangle(Triangle&& other);
    Triangle& operator=(Triangle&& other);

    std::array<Vertex, POINT_COUNT> m_vertices;
    std::array<unsigned short, VERTEX_COUNT> m_indices;
    glm::vec3 m_normal;
};

} // namespace rt

#endif // RT_TRIANGLE_H