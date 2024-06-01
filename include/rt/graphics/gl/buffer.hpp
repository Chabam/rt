#ifndef RT_BUFFER_H
#define RT_BUFFER_H

#include <rt/graphics/primitives/vertex.hpp>
#include <rt/utils/logger.hpp>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <span>

class Buffer
{
  public:
    Buffer(const std::span<const Vertex>& vertices);
    ~Buffer();

    void bind() const;
    const std::vector<Vertex>& get_data() const { return m_data; }

  private:
    GLuint m_vao;
    GLuint m_vbo;
    std::vector<Vertex> m_data;

    Logger m_logger{"Buffer"};
};

#endif // RT_BUFFER_H