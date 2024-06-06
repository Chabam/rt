#ifndef RT_PLANE_H
#define RT_PLANE_H

#include <rt/3d/mesh.hpp>
#include <rt/graphics/primitives/quad.hpp>

namespace rt
{

class Plane final : public Mesh
{
  public:
    Plane(float width, float height, const std::shared_ptr<Material>& material,
          const std::shared_ptr<Texture>& texture = {});

    uint32_t get_triangle_count() const override;

  private:
    Quad m_quad;
};

} // namespace rt

#endif // RT_PLANE_H