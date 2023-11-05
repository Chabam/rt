#pragma once
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <vector>

class Buffer
{
  public:
    Buffer(const std::vector<glm::vec3>& vertices);
    ~Buffer();

    void bind() const;

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    struct VerticeData;
    std::vector<VerticeData> m_data;

    void generateGlBuffers();
};
