#ifndef RT_BUFFER_H
#define RT_BUFFER_H

#include <rt/graphics/primitives/vertex.hpp>

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
    GLuint m_vao;
    GLuint m_vbo;
    std::span<const Vertex> m_data;
};

#endif // RT_BUFFER_H