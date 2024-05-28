#include <rt/3d/geometries/triangle.hpp>
#include <rt/3d/material.hpp>
#include <rt/3d/mesh.hpp>
#include <rt/graphics/gl/buffer.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/logger/logger.hpp>

#include <algorithm>

Mesh::Mesh(const Material& material)
    : Object3d(material)
{
}

void Mesh::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPos,
                  const Light& light)
{
    if (!m_buffer)
    {
        m_buffer = std::make_unique<Buffer>(getVerticeBufferData());
    }

    m_material.forwardUniforms(viewMatrix, m_model, m_normalMatrix, projectionMatrix, cameraPos, light);

    m_buffer->bind();
    glDrawArrays(GL_TRIANGLES, 0, getTriangleCount() * 3);
}