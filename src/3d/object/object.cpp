#include <rt/3d/object.hpp>
#include <rt/graphics/gl/buffer.hpp>

#include <glm/mat4x4.hpp>
#include <iostream>

Object3d::Object3d(const Material& material)
    : m_buffer()
    , m_material(material)
    , m_model(glm::mat4(1.f))
    , m_normalMatrix(glm::transpose(glm::inverse(m_model)))
{
}

Object3d::~Object3d()
{
}

const glm::mat4& Object3d::getModel() const
{
    return m_model;
}

void Object3d::setModel(const glm::mat4& trans)
{
    m_model = trans;
    m_normalMatrix = glm::transpose(glm::inverse(m_model));
}
