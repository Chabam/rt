#ifndef RT_CUBE_H
#define RT_CUBE_H

#include <rt/3d/geometries/geometry.hpp>
#include <rt/3d/geometries/quad.hpp>
#include <rt/3d/mesh.hpp>

#include <array>
#include <memory>

namespace rt
{

class Cube final : public Geometry
{
  public:
    static constexpr auto POINT_COUNT = 8;
    static constexpr auto QUAD_COUNT = 6;

    Cube(float width = 1.f, float height = 1.f, float depth = 1.f);

    std::span<const Vertex> get_vertices() const override;
    std::span<const unsigned short> get_indices() const override;

  private:
    float m_width;
    float m_height;
    float m_depth;

    std::array<Quad, QUAD_COUNT> m_quads;
    std::array<Vertex, QUAD_COUNT * Quad::POINT_COUNT> m_vertices;
    std::array<unsigned short, QUAD_COUNT * Quad::VERTEX_COUNT> m_indices;
};

} // namespace rt

#endif // RT_CUBE_H