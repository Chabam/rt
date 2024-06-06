#include <rt/3d/materials/blinn_phong.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/graphics/gl/shader_program.hpp>
#include <rt/utils/file_handler.hpp>

namespace rt
{

// TODO: Should be in a cache (precompiled or not)
static const std::shared_ptr<ShaderProgram>& get_blinn_phong_shader()
{
    static std::shared_ptr<ShaderProgram> blinn_phong_shader;
    if (blinn_phong_shader)
        return blinn_phong_shader;

    blinn_phong_shader = std::make_shared<ShaderProgram>();
    static std::shared_ptr<Shader> blinn_phong_vert = std::make_shared<Shader>(
        Shader::Type::Vertex, FileHandler::get_file_as_text("resources/shaders/blinn-phong.vert").c_str());
    static std::shared_ptr<Shader> blinn_phong_frag = std::make_shared<Shader>(
        Shader::Type::Fragment, FileHandler::get_file_as_text("resources/shaders/blinn-phong.frag").c_str());

    blinn_phong_shader->attach_shader(blinn_phong_vert);
    blinn_phong_shader->attach_shader(blinn_phong_frag);
    blinn_phong_shader->link();

    return blinn_phong_shader;
}

BlinnPhong::BlinnPhong(const Properties& properties)
    : Material(get_blinn_phong_shader())
    , m_color(properties.m_color)
    , m_specular(properties.m_specular)
    , m_shininess(properties.m_shininess)
    , m_emitsLight(properties.m_emitsLight)
{
}

void BlinnPhong::forward_properties_uniforms() const
{
    m_shader->set_uniform("color", m_color);
    m_shader->set_uniform("specularStr", m_specular);
    m_shader->set_uniform("shininess", m_shininess);
    m_shader->set_uniform("emitsLight", m_emitsLight);
}

} // namespace rt