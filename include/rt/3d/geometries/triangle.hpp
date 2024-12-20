#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include <rt/3d/geometries/geometry.hpp>

#include <array>
#include <glm/ext/vector_float3.hpp>

namespace rt
{

class Triangle final : public Geometry
{
  public:
    static constexpr auto POINT_COUNT = 3;
    static constexpr auto VERTEX_COUNT = POINT_COUNT;

    Triangle(const std::array<glm::vec3, POINT_COUNT>& pts,
             const std::array<glm::vec2, Triangle::POINT_COUNT>& uvs = {glm::vec2{0.5f, 1.f}, glm::vec2{1.f, 0.f},
                                                                        glm::vec2{0.f, 0.f}});

    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);

    Triangle(Triangle&& other);
    Triangle& operator=(Triangle&& other);

    std::span<const Vertex> get_vertices() const override;
    std::span<const unsigned int> get_indices() const override;
    const glm::vec3& get_normal() const;
    const glm::vec3& get_tangent() const;
    const glm::vec3& get_bi_tangent() const;

  private:
    std::array<Vertex, POINT_COUNT> m_vertices;
    std::array<unsigned int, VERTEX_COUNT> m_indices;
    glm::vec3 m_normal;
    glm::vec3 m_tangent;
    glm::vec3 m_bi_tangent;
};

} // namespace rt

#endif // RT_TRIANGLE_H
