#include <rt/3d/camera/camera.hpp>
#include <rt/3d/geometries/triangle.hpp>
#include <rt/3d/material.hpp>
#include <rt/3d/mesh.hpp>
#include <rt/graphics/gl/buffer.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/logger/logger.hpp>

#include <algorithm>

Mesh::Mesh(const Material& material)
    : m_buffer()
    , m_material(material)
    , m_model(glm::mat4(1.f))
    , m_normalMatrix(glm::transpose(glm::inverse(m_model)))
{
}

Mesh::~Mesh()
{
}

const glm::mat4& Mesh::getModel() const
{
    return m_model;
}

void Mesh::setModel(const glm::mat4& trans)
{
    m_model = trans;
    m_normalMatrix = glm::transpose(glm::inverse(m_model));
}

void Mesh::render(const Camera& camera, const Light& light) const
{
    if (!m_buffer)
    {
        throw std::logic_error("Buffer is not generated!");
    }

    m_material.forwardUniforms(camera.getViewMatrix(), m_model, m_normalMatrix, camera.getProjectionMatrix(),
                               camera.getPosition(), light);

    m_buffer->bind();
    glDrawArrays(GL_TRIANGLES, 0, getTriangleCount() * Triangle::VERTICE_COUNT);
}