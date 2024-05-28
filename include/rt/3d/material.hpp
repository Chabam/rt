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

    void forwardUniforms(const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const glm::mat3& normalMatrix,
                         const glm::mat4& projectionMatrix, const glm::vec3 cameraPos, const Light& light) const;

  protected:
    virtual void forwardPropertiesUniforms() const = 0;

    std::shared_ptr<ShaderProgram> m_shader;
};

#endif // RT_MATERIAL_H