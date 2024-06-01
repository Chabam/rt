#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include <rt/graphics/primitives/vertex.hpp>

#include <array>
#include <glm/vec3.hpp>

struct Triangle
{
    static constexpr auto POINT_COUNT = 3;
    static constexpr auto VERTEX_COUNT = POINT_COUNT;

    Triangle(const std::array<glm::vec3, POINT_COUNT>& pts);
    Triangle(const std::array<std::tuple<glm::vec3, unsigned short>, POINT_COUNT>& idx_pts);

    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);

    Triangle(Triangle&& other);
    Triangle& operator=(Triangle&& other);

    std::array<Vertex, POINT_COUNT> m_vertices;
    std::array<unsigned short, VERTEX_COUNT> m_indices;
    glm::vec3 m_normal;
};

#endif // RT_TRIANGLE_H