#pragma once
#include <object/mesh.h>
#include <object/geometries/quad.h>

#include <array>

class Cube : public Mesh
{
  public:
    Cube(unsigned int width, unsigned int height, unsigned int depth, const std::shared_ptr<Shader>& shader,
         const Material& material = Material(), const glm::mat4 model = glm::mat4(1));

  private:
    std::array<Quad, 6> m_quadParts;

    static std::array<Quad, 6> generateQuads(unsigned int width, unsigned int height, unsigned int depth);
};