#ifndef RT_SHADER_H
#define RT_SHADER_H

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

class Shader
{
  public:
    Shader(const char* vertSrc, const char* fragSrc);
    ~Shader();
    void use() const;
    void setMatrixUniform(const char* varName, const glm::mat4& matrix);
    void setMatrixUniform(const char* varName, const glm::mat3& matrix);
    void setVectorUniform(const char* varName, const glm::vec4& vector);
    void setVectorUniform(const char* varName, const glm::vec3& vector);
    void setFloatUniform(const char* varName, float value);
    void setIntUniform(const char* varName, int value);

  private:
    GLuint m_programUid;

    static void compileShaderSource(GLuint& shaderUid, GLenum type, const GLchar* source);
};

#endif // RT_SHADER_H