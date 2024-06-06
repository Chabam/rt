#include <rt/3d/camera/camera.hpp>
#include <rt/3d/light/light.hpp>
#include <rt/3d/material.hpp>
#include <rt/3d/mesh.hpp>
#include <rt/graphics/gl/shader_program.hpp>

namespace rt
{

Material::Material(const std::shared_ptr<ShaderProgram>& shader)
    : m_shader(shader)
{
}

Material::~Material()
{
}

void Material::forward_uniforms(const Mesh& mesh, const Camera& camera, const Light& light) const
{
    m_shader->use();

    m_shader->set_uniform("view", camera.get_view());
    m_shader->set_uniform("model", mesh.get_model());
    m_shader->set_uniform("projection", camera.get_projection());
    m_shader->set_uniform("normalMatrix", mesh.get_normal_matrix());
    m_shader->set_uniform("hasTexture", mesh.has_texture());

    m_shader->set_uniform("cameraPos", camera.get_position());

    m_shader->set_uniform("ambientStr", light.m_ambient);
    m_shader->set_uniform("lightPos", light.m_pos);
    m_shader->set_uniform("lightColor", light.m_color);

    forward_properties_uniforms();
}

} // namespace rt