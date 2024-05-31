#ifndef RT_CUBE_H
#define RT_CUBE_H

#include <rt/3d/mesh.hpp>
#include <rt/graphics/primitives/quad.hpp>

#include <array>

// TODO: Implement indices
class Cube final : public Mesh
{
  public:
    Cube(float width, float height, float depth, const std::shared_ptr<Material>& material);

    uint32_t get_triangle_count() const override;

  private:
    std::array<Quad, 6> m_quads;
};

#endif // RT_CUBE_H