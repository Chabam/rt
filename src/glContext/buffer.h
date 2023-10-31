#pragma once
#include <array>
#include <glad/glad.h>
#include <initializer_list>
#include <vector>
#include <glm/vec3.hpp>

class Buffer
{
  public:
    static constexpr auto COORD_DATA = 3; // x, y, z
    static constexpr auto VERTICE_DATA_SIZE = COORD_DATA;
    static constexpr auto VERTICE_POINTER_SIZE = VERTICE_DATA_SIZE * sizeof(GLfloat);
    typedef std::array<GLfloat, VERTICE_DATA_SIZE> VerticeData;

    Buffer() = default;
    Buffer(const std::vector<glm::vec3> &vertices);
    Buffer(const Buffer &other);
    Buffer& operator=(const Buffer& other);
    ~Buffer();

    void bind() const;
    void unbind() const;

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    std::vector<VerticeData> m_data;

    void generateGlBuffers();
};
