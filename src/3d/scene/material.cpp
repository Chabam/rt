#include <rt/3d/light/light.hpp>
#include <rt/3d/material.hpp>
#include <rt/graphics/gl/shaderProgram.hpp>

Material::Material(const std::shared_ptr<ShaderProgram>& shader)
    : m_shader(shader)
{
}

void Material::forwardUniforms(const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const glm::mat3& normalMatrix,
                               const glm::mat4& projectionMatrix, const glm::vec3 cameraPos, const Light& light) const
{
    m_shader->use();

    m_shader->setMatrixUniform("view", viewMatrix);
    m_shader->setMatrixUniform("model", modelMatrix);
    m_shader->setMatrixUniform("projection", projectionMatrix);
    m_shader->setMatrixUniform("normalMatrix", normalMatrix);

    m_shader->setVectorUniform("cameraPos", cameraPos);

    m_shader->setFloatUniform("ambientStr", light.m_ambient);
    m_shader->setVectorUniform("lightPos", light.m_pos);
    m_shader->setVectorUniform("lightColor", light.m_color);

    forwardPropertiesUniforms();
}