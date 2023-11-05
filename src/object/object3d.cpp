#include "object3d.h"

#include <glad/glad.h>
#include <iostream>

Object3d::Object3d(const std::vector<glm::vec3>& vertices, const std::shared_ptr<Shader>& shader, const Material& material,
                   const glm::mat4 model)
    : m_buffer(std::make_unique<Buffer>(vertices))
    , m_shader(shader)
    , m_material(material)
    , m_model(model)
{
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
    m_shader->use();
    m_shader->setVectorUniform("color", m_material.m_color);
    m_shader->setMatrixUniform("view", viewMatrix);
    m_shader->setMatrixUniform("model", m_model);
    m_shader->setMatrixUniform("projection", projectionMatrix);

    m_buffer->bind();
    glDrawArrays(GL_TRIANGLES, 0, getTriangleCount() * 3);
}
