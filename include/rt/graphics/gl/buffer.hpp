#ifndef RT_BUFFER_H
#define RT_BUFFER_H

#include <rt/graphics/gl/verticeBufferData.hpp>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <vector>

class Buffer
{
  public:
    Buffer(const std::vector<VerticeBufferData>& vertices);
    ~Buffer();

    void bind() const;

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    std::vector<VerticeBufferData> m_data;

    void generateGlBuffers();
};

#endif // RT_BUFFER_H