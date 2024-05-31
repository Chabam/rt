#include <rt/3d/light/light.hpp>
#include <rt/3d/material.hpp>
#include <rt/graphics/gl/shader_program.hpp>

Material::Material(const std::shared_ptr<ShaderProgram>& shader)
    : m_shader(shader)
{
}

void Material::forward_uniforms(const glm::mat4& view, const glm::mat4& model, const glm::mat3& normal,
                                const glm::mat4& projection, const glm::vec3 camera_pos, const Light& light) const
{
    m_shader->use();

    m_shader->set_uniform("view", view);
    m_shader->set_uniform("model", model);
    m_shader->set_uniform("projection", projection);
    m_shader->set_uniform("normalMatrix", normal);

    m_shader->set_uniform("cameraPos", camera_pos);

    m_shader->set_uniform("ambientStr", light.m_ambient);
    m_shader->set_uniform("lightPos", light.m_pos);
    m_shader->set_uniform("lightColor", light.m_color);

    forward_properties_uniforms();
}