#pragma once
#include <object/mesh.h>
#include <object/quadPrimitive.h>
#include <object/trianglePrimitive.h>

#include <array>

class Quad : public Mesh, public QuadPrimitive
{
  public:
    Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4,
         const std::shared_ptr<Shader>& shader, const Material& material = Material(),
         const glm::mat4 model = glm::mat4(1));
    Quad(const Quad& other);
    Quad& operator=(const Quad& other);
};