#include <rt/graphics/gl/buffer.hpp>
#include <rt/logger/logger.hpp>

#include <algorithm>
#include <array>

Buffer::Buffer(std::span<const VerticeBufferData> vertices)
    : m_VAO()
    , m_VBO()
    , m_data()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    constexpr auto POSITION_SIZE = decltype(VerticeBufferData::m_position)::length();
    constexpr auto NORMAL_SIZE = decltype(VerticeBufferData::m_normal)::length();
    constexpr auto VERTICE_DATA_SIZE = POSITION_SIZE + NORMAL_SIZE;
    constexpr auto VERTICE_POINTER_SIZE = VERTICE_DATA_SIZE * sizeof(GLfloat);

    const auto VERTICES_COUNT = vertices.size();
    const auto TOTAL_DATA_SIZE = VERTICES_COUNT * VERTICE_DATA_SIZE * sizeof(GLfloat);
    const auto START_COORD = (void*)0;
    const auto START_NORMAL = (void*)(3 * sizeof(float));

    m_data.reserve(vertices.size());
    for (const auto& verticeData : vertices)
    {
        VerticeBufferData::FloatValues floatValues(verticeData);
        m_data.insert(m_data.end(), floatValues.begin(), floatValues.end());
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, TOTAL_DATA_SIZE, m_data.data(), GL_STATIC_DRAW);

    glBindVertexArray(m_VAO);

    // Position
    glVertexAttribPointer(0, POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTICE_POINTER_SIZE, START_COORD);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, NORMAL_SIZE, GL_FLOAT, GL_FALSE, VERTICE_POINTER_SIZE, START_NORMAL);
    glEnableVertexAttribArray(1);
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