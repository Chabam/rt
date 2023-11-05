#include "object3d.h"

#include <glContext/buffer.h>
#include <glContext/shader.h>
#include <glm/mat4x4.hpp>
#include <iostream>

Object3d::Object3d(const std::shared_ptr<Shader>& shader, const Material& material)
    : m_shader(shader)
    , m_material(material)
    , m_model(glm::mat4(1.f))
    , m_buffer()
{
}

Object3d::~Object3d()
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

void Object3d::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const Light& light) const
{
    if (!m_buffer)
    {
        throw std::runtime_error("Buffer for object not set!");
    }

    m_shader->use();

    m_shader->setMatrixUniform("view", viewMatrix);
    m_shader->setMatrixUniform("model", m_model);
    m_shader->setMatrixUniform("projection", projectionMatrix);
 
    m_shader->setVectorUniform("color", m_material.m_color);

    m_shader->setFloatUniform("ambient", light.m_ambient);
    m_shader->setVectorUniform("lightPos", light.m_pos);
    m_shader->setVectorUniform("lightColor", light.m_color);

    m_buffer->bind();
    glDrawArrays(GL_TRIANGLES, 0, getTriangleCount() * 3);
}
