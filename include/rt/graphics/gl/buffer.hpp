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
    Buffer(const std::span<const Vertex>& vertices, const std::span<const unsigned short>& indices);
    ~Buffer();

    void bind() const;
    void unbind() const;
    const std::vector<Vertex>& get_vertices() const { return m_vertices; }
    const std::vector<unsigned short>& get_indices() const { return m_indices; }

  private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned short> m_indices;

    Logger m_logger{"Buffer"};
};

#endif // RT_BUFFER_H