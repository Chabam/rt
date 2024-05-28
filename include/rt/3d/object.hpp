#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include <rt/3d/material.hpp>
#include <rt/graphics/gl/renderable.hpp>

#include <memory>

class Shader;
class Buffer;
class Object3d : public Renderable
{
  public:
    Object3d(const std::shared_ptr<Shader>& shader, const Material& material = Material());
    virtual ~Object3d();

    void setModel(const glm::mat4& trans);
    const Material& getMaterial() const;
    const glm::mat4& getModel() const;

  protected:
    std::shared_ptr<Shader> m_shader;
    std::unique_ptr<Buffer> m_buffer;
    Material m_material;
    glm::mat4 m_model;
    glm::mat3 m_normalMatrix;
};

#endif // RT_OBJECT_H