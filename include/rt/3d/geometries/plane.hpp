#ifndef RT_PLANE_H
#define RT_PLANE_H

#include <rt/3d/geometries/quad.hpp>
#include <rt/3d/mesh.hpp>

class Plane final : public Mesh
{
  public:
    Plane(float width, float height, const Material& material);
    Plane(const Plane& other);
    Plane& operator=(const Plane& other);

    uint32_t getTriangleCount() const override;

  private:
    Quad m_quad;
};

#endif // RT_PLANE_H