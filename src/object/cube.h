#pragma once
#include <array>
#include <object/mesh.h>
#include <object/quadPrimitive.h>

class Cube : public Mesh
{
  public:
    Cube(uint8_t width, uint8_t height, uint8_t depth, const std::shared_ptr<Shader>& shader,
         const Material& material = Material(), const glm::mat4 model = glm::mat4(1));

  private:
    std::array<QuadPrimitive, 6> m_quads;

    static std::array<QuadPrimitive, 6> generateQuads(uint8_t width, uint8_t height, uint8_t depth);
    static std::vector<TrianglePrimitive> getTrianglesFromQuads(std::array<QuadPrimitive, 6> quads);
};