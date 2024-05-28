#include <rt/3d/materials/blinnPhong.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/graphics/gl/shaderProgram.hpp>
#include <rt/resourceLoader/resourceLoader.hpp>

static std::shared_ptr<ShaderProgram> getBlinnPhongShader()
{
    static std::shared_ptr<ShaderProgram> blinnPhongShader;
    if (blinnPhongShader)
        return blinnPhongShader;

    blinnPhongShader = std::make_shared<ShaderProgram>();
    std::shared_ptr<Shader> blinnPhongVertexShader = std::make_shared<Shader>(
        Shader::Type::Vertex, ResourceLoader::read_file("resources/shaders/blinn-phong.vert").c_str());
    std::shared_ptr<Shader> blinnPhongFragment = std::make_shared<Shader>(
        Shader::Type::Fragment, ResourceLoader::read_file("resources/shaders/blinn-phong.frag").c_str());

    blinnPhongShader->attachShader(blinnPhongVertexShader);
    blinnPhongShader->attachShader(blinnPhongFragment);
    blinnPhongShader->link();

    return blinnPhongShader;
}

BlinnPhong::BlinnPhong(const Properties& properties)
    : Material(getBlinnPhongShader())
    , m_color(properties.m_color)
    , m_specular(properties.m_specular)
    , m_shininess(properties.m_shininess)
    , m_emitsLight(properties.m_emitsLight)
{
}

void BlinnPhong::forwardPropertiesUniforms() const
{
    m_shader->setVectorUniform("color", m_color);
    m_shader->setFloatUniform("specularStr", m_specular);
    m_shader->setIntUniform("shininess", m_shininess);
    m_shader->setIntUniform("emitsLight", m_emitsLight);
}