#ifndef RT_PLANE_H
#define RT_PLANE_H

#include <rt/3d/geometries/geometry.hpp>
#include <rt/3d/geometries/quad.hpp>

namespace rt
{

class Plane final : public Geometry
{
  public:
    Plane(float width = 1.f, float height = 1.f);

    std::span<const Vertex> get_vertices() const override;
    std::span<const unsigned int> get_indices() const override;

  private:
    Quad m_quad;
};

} // namespace rt

#endif // RT_PLANE_H
