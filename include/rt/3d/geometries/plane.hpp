#pragma once
#include <rt/3d/geometries/quad.hpp>
#include <rt/3d/mesh.hpp>

class Plane : public Mesh
{
  public:
    Plane(float width, float height, const std::shared_ptr<Shader>& shader, const Material& material = Material(),
          const glm::mat4 model = glm::mat4(1));
    Plane(const Plane& other);
    Plane& operator=(const Plane& other);

  private:
    Quad m_quad;
};