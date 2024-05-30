#ifndef RT_BUFFER_H
#define RT_BUFFER_H

#include <rt/graphics/gl/vertex.hpp>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <span>

class Buffer
{
  public:
    Buffer(const std::span<const Vertex>& vertices);
    ~Buffer();

    void bind() const;

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    std::span<const Vertex> m_data;
};

#endif // RT_BUFFER_H