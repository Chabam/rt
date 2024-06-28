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

    Triangle(const std::array<glm::vec3, POINT_COUNT>& pts);

    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);

    Triangle(Triangle&& other);
    Triangle& operator=(Triangle&& other);

    std::span<const Vertex> get_vertices() const override;
    std::span<const unsigned int> get_indices() const override;
    const glm::vec3& get_normal() const;

  private:
    std::array<Vertex, POINT_COUNT> m_vertices;
    std::array<unsigned int, VERTEX_COUNT> m_indices;
    glm::vec3 m_normal;
};

} // namespace rt

#endif // RT_TRIANGLE_H