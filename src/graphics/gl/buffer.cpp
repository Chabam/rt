#include <rt/graphics/gl/buffer.hpp>
#include <rt/logger/logger.hpp>

#include <algorithm>
#include <array>
#include <cstddef>

Buffer::Buffer(const std::span<const Vertex>& vertices)
    : m_VAO()
    , m_VBO()
    , m_data(vertices)
{
    glCreateBuffers(1, &m_VBO);
    glNamedBufferStorage(m_VBO, sizeof(Vertex) * m_data.size(), m_data.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &m_VAO);

    glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(Vertex));

    for (const VertexAttributeDescription& verticesAttribute : Vertex::getAttributesDescription())
    {
        glEnableVertexArrayAttrib(m_VAO, verticesAttribute.m_location);
        glVertexArrayAttribFormat(m_VAO, verticesAttribute.m_location, verticesAttribute.m_count,
                                  verticesAttribute.m_type, GL_FALSE, verticesAttribute.m_offset);
        glVertexArrayAttribBinding(m_VAO, verticesAttribute.m_location, 0);
    }
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Buffer::bind() const
{
    glBindVertexArray(m_VAO);
}