#include "object3d.h"

#include <glContext/buffer.h>
#include <glContext/shader.h>
#include <glm/mat4x4.hpp>
#include <iostream>

Object3d::Object3d(const std::shared_ptr<Shader>& shader, const Material& material)
    : m_shader(shader)
    , m_material(material)
    , m_model(glm::mat4(1.f))
    , m_normalMatrix(glm::transpose(glm::inverse(m_model)))
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
    m_normalMatrix = glm::transpose(glm::inverse(m_model));
}

const Material& Object3d::getMaterial() const
{
    return m_material;
}
