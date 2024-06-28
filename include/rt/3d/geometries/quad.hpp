#ifndef RT_QUAD_H
#define RT_QUAD_H

#include <rt/3d/geometries/geometry.hpp>
#include <rt/3d/geometries/triangle.hpp>

#include <array>
#include <glm/ext/vector_float3.hpp>

namespace rt
{

class Quad final : public Geometry
{
  public:
    static constexpr auto POINT_COUNT = 4;
    static constexpr auto TRIANGLE_COUNT = 2;
    static constexpr auto VERTEX_COUNT = Triangle::VERTEX_COUNT * TRIANGLE_COUNT;

    Quad() = default;
    Quad(const std::array<glm::vec3, POINT_COUNT>& pts);

    Quad(const Quad& other);
    Quad& operator=(const Quad& other);

    Quad(Quad&& other);
    Quad& operator=(Quad&& other);

    std::span<const Vertex> get_vertices() const override;
    std::span<const unsigned int> get_indices() const override;
    const glm::vec3& get_normal() const;

  private:
    std::array<Vertex, POINT_COUNT> m_vertices;
    std::array<unsigned int, VERTEX_COUNT> m_indices;
    glm::vec3 m_normal;
};

} // namespace rt

#endif // RT_QUAD_H