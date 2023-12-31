#pragma once
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <vector>
#include <glContext/verticeBufferData.h>

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
