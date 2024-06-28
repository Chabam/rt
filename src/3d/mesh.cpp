#include "glad/gl.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/matrix.hpp"

#include <rt/3d/camera/camera.hpp>
#include <rt/3d/geometries/geometry.hpp>
#include <rt/3d/material.hpp>
#include <rt/3d/mesh.hpp>
#include <rt/graphics/gl/buffer.hpp>
#include <rt/graphics/gl/texture.hpp>

#include <memory>
#include <stdexcept>
#include <utility>

namespace rt
{

Mesh::Mesh(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material,
           const std::shared_ptr<Texture>& texture)
    : m_geometry{geometry}
    , m_buffer{std::make_unique<Buffer>(m_geometry->get_vertices(), geometry->get_indices())}
    , m_material{material}
    , m_texture{texture}
    , m_model{glm::mat4(1.f)}
    , m_normal_matrix{glm::transpose(glm::inverse(m_model))}
{
}

Mesh::Mesh(const Mesh& other)
    : m_geometry{other.m_geometry}
    , m_buffer{std::make_unique<Buffer>(m_geometry->get_vertices(), m_geometry->get_indices())}
    , m_material{other.m_material}
    , m_texture{other.m_texture}
    , m_model{other.m_model}
    , m_normal_matrix{other.m_normal_matrix}
{
}

Mesh& Mesh::operator=(const Mesh& other)
{
    m_geometry = other.m_geometry;
    m_buffer = std::make_unique<Buffer>(m_geometry->get_vertices(), m_geometry->get_indices());
    m_material = other.m_material;
    m_texture = other.m_texture;
    m_model = other.m_model;
    m_normal_matrix = other.m_normal_matrix;

    return *this;
}

Mesh::Mesh(Mesh&& other)
    : m_geometry{std::move(other.m_geometry)}
    , m_buffer{std::move(other.m_buffer)}
    , m_material{std::move(other.m_material)}
    , m_texture{std::move(other.m_texture)}
    , m_model{std::move(other.m_model)}
    , m_normal_matrix{std::move(other.m_normal_matrix)}
{
}

Mesh& Mesh::operator=(Mesh&& other)
{
    m_geometry = std::move(other.m_geometry);
    m_buffer = std::move(other.m_buffer);
    m_material = std::move(other.m_material);
    m_texture = std::move(other.m_texture);
    m_model = std::move(other.m_model);
    m_normal_matrix = std::move(other.m_normal_matrix);

    return *this;
}

Mesh::~Mesh()
{
}

void Mesh::render(const Camera& camera, const Light& light) const
{
    if (!m_buffer)
    {
        throw std::logic_error("Buffer is not generated!");
    }

    m_material->forward_uniforms(*this, camera, light);

    m_buffer->bind();

    if (m_texture)
    {
        m_texture->bind();
    }

    glDrawElements(GL_TRIANGLES, m_geometry->get_indices().size(), GL_UNSIGNED_INT, nullptr);

    m_buffer->unbind();

    if (m_texture)
    {
        m_texture->unbind();
    }
}

void Mesh::set_model(const glm::mat4& trans)
{
    m_model = trans;
    m_normal_matrix = glm::transpose(glm::inverse(m_model));
}

const glm::mat4& Mesh::get_model() const
{
    return m_model;
}
const glm::mat3& Mesh::get_normal_matrix() const
{
    return m_normal_matrix;
}
bool Mesh::has_texture() const
{
    return m_texture.use_count() != 0;
}

} // namespace rt