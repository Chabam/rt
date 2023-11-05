#include "buffer.h"

#include <algorithm>
#include <array>
#include <utils/logger.h>

struct Buffer::VerticeData
{
    static constexpr auto COORD_DATA = 3; // x, y, z
    static constexpr auto VERTICE_DATA_SIZE = COORD_DATA;
    static constexpr auto VERTICE_POINTER_SIZE = VERTICE_DATA_SIZE * sizeof(GLfloat);
    using Impl = std::array<GLfloat, VERTICE_DATA_SIZE>;

    Impl m_impl;
};

Buffer::Buffer(const std::vector<glm::vec3>& vertices)
    : m_VAO()
    , m_VBO()
    , m_data()
{
    for (const glm::vec3& vertice : vertices)
    {
        m_data.push_back({vertice.x, vertice.y, vertice.z});
    }

    generateGlBuffers();
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Buffer::generateGlBuffers()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    const auto VERTICES_COUNT = m_data.size();
    const auto TOTAL_DATA_SIZE = VERTICES_COUNT * Buffer::VerticeData::VERTICE_DATA_SIZE * sizeof(GLfloat);
    const auto START_COORD = (void*)0;

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, TOTAL_DATA_SIZE, m_data.data(), GL_STATIC_DRAW);

    glBindVertexArray(m_VAO);

    glVertexAttribPointer(0, Buffer::VerticeData::COORD_DATA, GL_FLOAT, GL_FALSE,
                          Buffer::VerticeData::VERTICE_POINTER_SIZE, START_COORD);
    glEnableVertexAttribArray(0);
}

void Buffer::bind() const
{
    glBindVertexArray(m_VAO);
}