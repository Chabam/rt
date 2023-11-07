#pragma once
#include <glContext/buffer.h>
#include <glm/mat4x4.hpp>
#include <memory>
#include <object/material.h>
#include <object/light.h>

class Shader;

class Object3d
{
  public:
    Object3d(const std::shared_ptr<Shader>& shader, const Material& material = Material());
    ~Object3d();

    void applyTransformation(const glm::mat4& trans);
    const Material& getMaterial() const;
    const glm::mat4& getModel() const;
    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const Light& light) const;

    virtual uint32_t getTriangleCount() const = 0;

  protected:
    std::shared_ptr<Shader> m_shader;
    Material m_material;
    glm::mat4 m_model;
    std::unique_ptr<Buffer> m_buffer;
    glm::mat3 m_normalMatrix;
};