#include "buffer.h"

#include <algorithm>
#include <utils/logger.h>

Buffer::Buffer(const std::vector<glm::vec3>& vertices)
    : m_VAO()
    , m_VBO()
    , m_data()
{
    // Converting the vertice object to a flat array of GLfloat
    for (const glm::vec3& vertice : vertices)
    {
        m_data.push_back({vertice.x, vertice.y, vertice.z});
    }

    generateGlBuffers();
}

Buffer::Buffer(const Buffer& other)
    : m_data(other.m_data)
{
    generateGlBuffers();
}

Buffer& Buffer::operator=(const Buffer& other)
{
    m_data = other.m_data;
    generateGlBuffers();

    return *this;
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Buffer::generateGlBuffers()
{
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    const auto VERTICES_COUNT = m_data.size();
    const auto TOTAL_DATA_SIZE = VERTICES_COUNT * VERTICE_DATA_SIZE * sizeof(GLfloat);
    const auto START_COORD = (void*)0;

    glVertexAttribPointer(0, COORD_DATA, GL_FLOAT, GL_FALSE, VERTICE_POINTER_SIZE, START_COORD);
    glEnableVertexAttribArray(0);

    glBufferData(GL_ARRAY_BUFFER, TOTAL_DATA_SIZE, m_data.data(), GL_STATIC_DRAW);
}

void Buffer::bind() const
{
    glBindVertexArray(m_VAO);
}