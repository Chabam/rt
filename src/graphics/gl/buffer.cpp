#include <rt/graphics/gl/buffer.hpp>
#include <rt/utils/logger.hpp>

#include <algorithm>
#include <array>
#include <cstddef>

Buffer::Buffer(const std::span<const Vertex>& vertices)
    : m_vao()
    , m_vbo()
    , m_data(vertices)
{
    glCreateBuffers(1, &m_vbo);
    glNamedBufferStorage(m_vbo, sizeof(Vertex) * m_data.size(), m_data.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &m_vao);

    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));

    for (const VertexAttributeDescription& verticesAttribute : Vertex::getAttributesDescription())
    {
        glEnableVertexArrayAttrib(m_vao, verticesAttribute.m_location);
        glVertexArrayAttribFormat(m_vao, verticesAttribute.m_location, verticesAttribute.m_count,
                                  verticesAttribute.m_type, GL_FALSE, verticesAttribute.m_offset);
        glVertexArrayAttribBinding(m_vao, verticesAttribute.m_location, 0);
    }
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void Buffer::bind() const
{
    glBindVertexArray(m_vao);
}