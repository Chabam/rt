#ifndef RT_CUBE_H
#define RT_CUBE_H

#include <rt/3d/mesh.hpp>
#include <rt/graphics/primitives/quad.hpp>

#include <array>

namespace rt
{

class Cube final : public Mesh
{
  public:
    static constexpr auto POINT_COUNT = 8;

    Cube(float width, float height, float depth, const std::shared_ptr<Material>& material,
         const std::shared_ptr<Texture>& texture = {});

    uint32_t get_triangle_count() const override;

  private:
    std::array<Quad, 6> m_quads;
};

} // namespace rt

#endif // RT_CUBE_H