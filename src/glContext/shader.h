#pragma once
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <object/material.h>
#include <sstream>
#include <string>

class Shader
{
  public:
    Shader(const char* vertSrc, const char* fragSrc);
    ~Shader();
    void bind() const;
    void unbind() const;
    void setMatrixUniform(const char* varName, const glm::mat4& matrix);
    void setVectorUniform(const char* varName, const glm::vec4& vector);

  private:
    GLuint m_vertUid;
    GLuint m_fragUid;
    GLuint m_programUid;

    static void compileShaderSource(GLuint& shaderUid, GLenum type, const GLchar* source);
};