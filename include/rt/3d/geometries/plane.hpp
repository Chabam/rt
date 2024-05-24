#pragma once
#include <rt/3d/geometries/quad.hpp>
#include <rt/3d/mesh.hpp>

class Plane final : public Mesh
{
  public:
    Plane(float width, float height, const std::shared_ptr<Shader>& shader, const Material& material = Material());
    Plane(const Plane& other);
    Plane& operator=(const Plane& other);

    uint32_t getTriangleCount() const override;
    std::vector<VerticeBufferData> getVerticeBufferData() const override;

  private:
    Quad m_quad;
};