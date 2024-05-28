#ifndef RT_SHADER_PROGRAM_H
#define RT_SHADER_PROGRAM_H

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <memory>

class Shader;

class ShaderProgram
{
  public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(const std::shared_ptr<Shader>& shader);
    void link();

    void use() const;
    void setMatrixUniform(const char* varName, const glm::mat4& matrix);
    void setMatrixUniform(const char* varName, const glm::mat3& matrix);
    void setVectorUniform(const char* varName, const glm::vec4& vector);
    void setVectorUniform(const char* varName, const glm::vec3& vector);
    void setFloatUniform(const char* varName, float value);
    void setIntUniform(const char* varName, int value);

  private:
    GLuint m_id;
    std::vector<std::shared_ptr<Shader>> m_attachedShaders;
};

#endif // RT_SHADER_PROGRAM_H