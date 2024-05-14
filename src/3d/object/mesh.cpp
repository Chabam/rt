#include <rt/3d/geometries/triangle.hpp>
#include <rt/3d/mesh.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/logger/logger.hpp>

#include <algorithm>

Mesh::Mesh(const std::shared_ptr<Shader>& shader, const Material& material)
    : Object3d(shader, material)
    , m_triangles()
{
}

void Mesh::setTriangles(const std::vector<Triangle>& triangles)
{
    m_triangles = triangles;
    std::vector<VerticeBufferData> vertices;
    vertices.reserve(triangles.size() * std::tuple_size<decltype(Triangle::m_p)>::value);

    for (const Triangle& triangle : m_triangles)
    {
        std::vector<VerticeBufferData> triangleVec{triangle};
        vertices.insert(vertices.end(), triangleVec.begin(), triangleVec.end());
    }

    m_buffer = std::make_unique<Buffer>(vertices);
}

uint32_t Mesh::getTriangleCount() const
{
    return m_triangles.size();
}

void Mesh::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPos,
                  const Light& light) const
{
    if (!m_buffer)
    {
        throw std::runtime_error("Buffer for object not set!");
    }

    m_shader->use();

    m_shader->setMatrixUniform("view", viewMatrix);
    m_shader->setMatrixUniform("model", m_model);
    m_shader->setMatrixUniform("projection", projectionMatrix);
    m_shader->setMatrixUniform("normalMatrix", m_normalMatrix);

    m_shader->setVectorUniform("cameraPos", cameraPos);

    m_shader->setVectorUniform("color", m_material.m_color);
    m_shader->setFloatUniform("specularStr", m_material.m_specular);
    m_shader->setIntUniform("shininess", m_material.m_shininess);
    m_shader->setIntUniform("emitsLight", m_material.m_emitsLight);

    m_shader->setFloatUniform("ambientStr", light.m_ambient);
    m_shader->setVectorUniform("lightPos", light.m_pos);
    m_shader->setVectorUniform("lightColor", light.m_color);

    m_buffer->bind();
    glDrawArrays(GL_TRIANGLES, 0, getTriangleCount() * 3);
}