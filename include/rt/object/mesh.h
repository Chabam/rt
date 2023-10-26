#pragma once

#include <glm/glm.hpp>
#include <rt/glContext/buffer.h>
#include <rt/object/material.h>
#include <rt/object/triangle.h>
#include <rt/object/vertice.h>
#include <vector>

class Mesh
{
  public:
    Mesh(const std::vector<Triangle> &triangles, const Material &material = Material());
    Mesh(const Mesh &other);
    Mesh &operator=(const Mesh &other);

    uint32_t getTriangleCount() const;
    std::vector<Vertice> getVertices() const;
    const glm::mat4 &getModel() const;
    void applyTransformation(const glm::mat4 &trans);
    const std::vector<Triangle> &getTriangles() const;
    const Material &getMaterial() const;

  protected:
    Mesh();
    std::vector<Triangle> m_triangles;
    glm::mat4 m_model;
    Material m_material;
};