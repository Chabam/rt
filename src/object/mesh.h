#pragma once
#include <glContext/buffer.h>
#include <object/material.h>
#include <object/object3d.h>
#include <object/trianglePrimitive.h>

#include <glm/glm.hpp>
#include <vector>

class Mesh : public Object3d
{
  public:
    Mesh(const std::vector<TrianglePrimitive>& triangles, const std::shared_ptr<Shader>& shader,
         const Material& material = Material(), const glm::mat4 model = glm::mat4(1));
    Mesh(const Mesh& other);
    Mesh& operator=(const Mesh& other);

    uint32_t getTriangleCount() const override;
    const std::vector<TrianglePrimitive>& getTriangles() const;

  protected:
    std::vector<TrianglePrimitive> m_triangles;
    
    static std::vector<glm::vec3> getVertices(const std::vector<TrianglePrimitive>& triangles);

};