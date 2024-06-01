#include <rt/3d/camera/camera.hpp>
#include <rt/3d/material.hpp>
#include <rt/3d/mesh.hpp>
#include <rt/graphics/gl/buffer.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/graphics/primitives/triangle.hpp>
#include <rt/utils/logger.hpp>

#include <algorithm>

Mesh::Mesh(const std::shared_ptr<Material>& material)
    : m_buffer{}
    , m_material{material}
    , m_model{glm::mat4(1.f)}
    , m_normal_matrix{glm::transpose(glm::inverse(m_model))}
{
}

Mesh::Mesh(const Mesh& other)
    : m_buffer{std::make_unique<Buffer>(other.m_buffer->get_vertices(), other.m_buffer->get_indices())}
    , m_material{other.m_material}
    , m_model{other.m_model}
    , m_normal_matrix{other.m_normal_matrix}
{
}

Mesh& Mesh::operator=(const Mesh& other)
{
    m_buffer = std::make_unique<Buffer>(other.m_buffer->get_vertices(), other.m_buffer->get_indices());
    m_material = other.m_material;
    m_model = other.m_model;
    m_normal_matrix = other.m_normal_matrix;

    return *this;
}

Mesh::Mesh(Mesh&& other)
    : m_buffer{std::move(other.m_buffer)}
    , m_material{std::move(other.m_material)}
    , m_model{std::move(other.m_model)}
    , m_normal_matrix{std::move(other.m_normal_matrix)}
{
}

Mesh& Mesh::operator=(Mesh&& other)
{
    m_buffer = std::move(other.m_buffer);
    m_material = std::move(other.m_material);
    m_model = std::move(other.m_model);
    m_normal_matrix = std::move(other.m_normal_matrix);

    return *this;
}

Mesh::~Mesh()
{
}

const glm::mat4& Mesh::get_model() const
{
    return m_model;
}

void Mesh::set_model(const glm::mat4& trans)
{
    m_model = trans;
    m_normal_matrix = glm::transpose(glm::inverse(m_model));
}

void Mesh::render(const Camera& camera, const Light& light) const
{
    if (!m_buffer)
    {
        throw std::logic_error("Buffer is not generated!");
    }

    m_material->forward_uniforms(camera.get_view(), m_model, m_normal_matrix, camera.get_projection(),
                                 camera.get_position(), light);

    m_buffer->bind();
    glDrawElements(GL_TRIANGLES, get_triangle_count() * Triangle::VERTEX_COUNT, GL_UNSIGNED_SHORT, nullptr);
}