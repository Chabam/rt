#pragma once
#include <object/object3d.h>

#include <glm/glm.hpp>
#include <vector>

class Triangle;

class Mesh : public Object3d
{
  public:
    Mesh(const std::shared_ptr<Shader>& shader, const Material& material = Material());

    uint32_t getTriangleCount() const override;
    const std::vector<Triangle>& getTriangles() const;

  protected:
    void setTriangles(const std::vector<Triangle>& triangles);
    std::vector<Triangle> m_triangles;
};