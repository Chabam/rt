#pragma once
#include <rt/3d/geometries/quad.hpp>
#include <rt/3d/mesh.hpp>

class QuadMesh : public Mesh, public Quad
{
  public:
    QuadMesh(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4,
             const std::shared_ptr<Shader>& shader, const Material& material = Material(),
             const glm::mat4 model = glm::mat4(1));
    QuadMesh(const QuadMesh& other);
    QuadMesh& operator=(const QuadMesh& other);

    void swap(QuadMesh& other);
};