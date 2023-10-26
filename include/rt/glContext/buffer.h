#pragma once

#include <array>
#include <glad/gl.h>
#include <initializer_list>
#include <rt/object/color.h>
#include <rt/object/vertice.h>
#include <vector>

class Buffer
{
  public:
    static const auto COORD_DATA = 3; // x, y, z
    static const auto VERTICE_DATA_SIZE = COORD_DATA;
    static const auto VERTICE_POINTER_SIZE = VERTICE_DATA_SIZE * sizeof(GLfloat);
    typedef std::array<GLfloat, VERTICE_DATA_SIZE> VerticeData;

    Buffer(const std::vector<Vertice> &vertices);
    Buffer(Buffer &&other);
    ~Buffer();

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    std::vector<VerticeData> m_data;
};
