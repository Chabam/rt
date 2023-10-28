#include "buffer.h"
#include "logger/logger.h"
#include <algorithm>

Buffer::Buffer(const std::vector<Vertice> &vertices)
{
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Converting the vertice object to a flat array of GLfloat
    for (const Vertice &vertice : vertices)
    {
        // clang-format off
        m_data.push_back({{
            vertice.x,
            vertice.y,
            vertice.z
        }});
        // clang-format on
    }

    const auto VERTICES_COUNT = vertices.size();
    const auto TOTAL_DATA_SIZE = VERTICES_COUNT * VERTICE_DATA_SIZE * sizeof(GLfloat);
    const auto START_COORD = (void *)0;

    glVertexAttribPointer(0, COORD_DATA, GL_FLOAT, GL_FALSE, VERTICE_POINTER_SIZE, START_COORD);
    glEnableVertexAttribArray(0);

    glBufferData(GL_ARRAY_BUFFER, TOTAL_DATA_SIZE, m_data.data(), GL_STATIC_DRAW);
}

Buffer::Buffer(Buffer &&other)
{
    m_VAO = other.m_VAO;
    m_VBO = other.m_VBO;

    other.m_VAO = 0;
    other.m_VBO = 0;
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}
