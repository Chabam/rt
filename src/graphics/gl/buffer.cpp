#include <rt/graphics/gl/buffer.hpp>
#include <rt/utils/logger.hpp>

#include <algorithm>
#include <array>
#include <cstddef>

namespace rt
{

Buffer::Buffer(const std::span<const Vertex>& vertices, const std::span<const unsigned short>& indices)
    : m_vao{}
    , m_vbo{}
    , m_ibo{}
    , m_vertices{}
    , m_indices{}
{
    m_vertices.assign(vertices.begin(), vertices.end());
    m_indices.assign(indices.begin(), indices.end());

    glCreateBuffers(1, &m_vbo);
    glNamedBufferStorage(m_vbo, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &m_ibo);
    glNamedBufferStorage(m_ibo, sizeof(unsigned short) * m_indices.size(), m_indices.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &m_vao);
    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));
    glVertexArrayElementBuffer(m_vao, m_ibo);

    m_logger.add_subcategory(std::vformat("vbo:{},vao:{},ibo:{}", std::make_format_args(m_vbo, m_vao, m_ibo)));

    for (const VertexAttributeLayout& verticesAttribute : Vertex::get_attributes_layout())
    {
        glEnableVertexArrayAttrib(m_vao, verticesAttribute.m_location);
        glVertexArrayAttribFormat(m_vao, verticesAttribute.m_location, verticesAttribute.m_count,
                                  verticesAttribute.m_type, GL_FALSE, verticesAttribute.m_offset);
        glVertexArrayAttribBinding(m_vao, verticesAttribute.m_location, 0);
    }

    m_logger.debug("Created with {} vertices", m_vertices.size());
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    glDeleteVertexArrays(1, &m_vao);
    m_logger.debug("Buffer destroyed");
}

void Buffer::bind() const
{
    glBindVertexArray(m_vao);
}

void Buffer::unbind() const
{
    glBindVertexArray(0);
}

} // namespace rt