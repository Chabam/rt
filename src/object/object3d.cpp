#include "object3d.h"

#include <glad/glad.h>

Object3d::Object3d(const Buffer& buffer, const std::shared_ptr<Shader>& shader, const Material& material,
                   const glm::mat4 model)
    : m_buffer(buffer)
    , m_shader(shader)
    , m_material(material)
    , m_model(model)
{
}

Object3d::Object3d(const Object3d& other)
{
    m_buffer = other.m_buffer;
    m_shader = other.m_shader;
    m_material = other.m_material;
    m_model = other.m_model;
}

Object3d& Object3d::operator=(const Object3d& other)
{
    m_buffer = other.m_buffer;
    m_shader = other.m_shader;
    m_material = other.m_material;
    m_model = other.m_model;

    return *this;
}

const glm::mat4& Object3d::getModel() const
{
    return m_model;
}

void Object3d::applyTransformation(const glm::mat4& trans)
{
    m_model = m_model * trans;
}

const Material& Object3d::getMaterial() const
{
    return m_material;
}

void Object3d::render(const glm::mat4& viewMatrix, const glm::mat4 projectionMatrix) const
{
    m_shader->bind();
    m_buffer.bind();
    glDrawArrays(GL_TRIANGLES, 0, getTriangleCount() * 3);
    m_shader->setUniforms(m_material, m_model, viewMatrix, projectionMatrix);
    m_shader->unbind();
}
