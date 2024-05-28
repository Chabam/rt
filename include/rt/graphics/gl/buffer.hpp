#ifndef RT_BUFFER_H
#define RT_BUFFER_H

#include <rt/graphics/gl/verticeBufferData.hpp>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <span>

class Buffer
{
  public:
    Buffer(std::span<const VerticeBufferData> vertices);
    ~Buffer();

    void bind() const;

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    std::vector<GLfloat> m_data;
};

#endif // RT_BUFFER_H