#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include <rt/3d/light/light.hpp>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>

class ShaderProgram;

class Material
{
  public:
    Material(const std::shared_ptr<ShaderProgram>& shader);

    void forward_uniforms(const glm::mat4& view, const glm::mat4& model, const glm::mat3& normal,
                          const glm::mat4& projection, const glm::vec3 camera_pos, const Light& light) const;

  protected:
    virtual void forward_properties_uniforms() const = 0;

    const std::shared_ptr<ShaderProgram>& m_shader;
};

#endif // RT_MATERIAL_H