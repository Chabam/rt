#pragma once
#include <rt/3d/geometries/quad.hpp>
#include <rt/3d/mesh.hpp>

#include <array>

class Cube final : public Mesh
{
  public:
    Cube(float width, float height, float depth, const std::shared_ptr<Shader>& shader,
         const Material& material = Material());

    uint32_t getTriangleCount() const override;
    std::vector<VerticeBufferData> getVerticeBufferData() const override;

  private:
    std::array<Quad, 6> m_quadParts;
};