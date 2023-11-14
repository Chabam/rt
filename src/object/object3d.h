#pragma once
#include <glContext/buffer.h>
#include <glContext/renderable.h>
#include <memory>
#include <object/light/light.h>
#include <object/material.h>

class Shader;

class Object3d : public Renderable
{
  public:
    Object3d(const std::shared_ptr<Shader>& shader, const Material& material = Material());
    ~Object3d();

    void applyTransformation(const glm::mat4& trans);
    const Material& getMaterial() const;
    const glm::mat4& getModel() const;

  protected:
    std::shared_ptr<Shader> m_shader;
    Material m_material;
    glm::mat4 m_model;
    std::unique_ptr<Buffer> m_buffer;
    glm::mat3 m_normalMatrix;
};