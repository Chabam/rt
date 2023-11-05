#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

class Shader
{
  public:
    Shader(const char* vertSrc, const char* fragSrc);
    ~Shader();
    void use() const;
    void setMatrixUniform(const char* varName, const glm::mat4& matrix);
    void setVectorUniform(const char* varName, const glm::vec4& vector);

  private:
    GLuint m_programUid;

    static void compileShaderSource(GLuint& shaderUid, GLenum type, const GLchar* source);
};