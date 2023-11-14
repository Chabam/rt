#pragma once
#include <object/object3d.h>

#include <glm/glm.hpp>
#include <vector>

class Triangle;

class Mesh : public Object3d
{
  public:
    Mesh(const std::shared_ptr<Shader>& shader, const Material& material = Material());

    uint32_t getTriangleCount() const;

    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPos,
                const Light& light) const;

  protected:
    void setTriangles(const std::vector<Triangle>& triangles);
    std::vector<Triangle> m_triangles;
};