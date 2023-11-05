#pragma once
#include <glContext/buffer.h>
#include <glContext/shader.h>
#include <memory>
#include <object/material.h>

class Object3d
{
  public:
    Object3d(const std::vector<glm::vec3>& vertices, const std::shared_ptr<Shader>& shader, const Material& material = Material(),
             const glm::mat4 model = glm::mat4(1.f));

    void applyTransformation(const glm::mat4& trans);
    const Material& getMaterial() const;
    const glm::mat4& getModel() const;
    void render(const glm::mat4& viewMatrix, const glm::mat4 projectionMatrix) const;

    virtual uint32_t getTriangleCount() const = 0;
  protected:
    std::unique_ptr<Buffer> m_buffer;
    Material m_material;
    glm::mat4 m_model;
    std::shared_ptr<Shader> m_shader;
};