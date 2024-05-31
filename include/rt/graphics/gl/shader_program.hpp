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

    void attach_shader(const std::shared_ptr<Shader>& shader);
    void link();

    void use() const;

    void set_uniform(const char* var_name, const glm::mat4& matrix);
    void set_uniform(const char* var_name, const glm::mat3& matrix);
    void set_uniform(const char* var_name, const glm::vec4& vector);
    void set_uniform(const char* var_name, const glm::vec3& vector);
    void set_uniform(const char* var_name, float value);
    void set_uniform(const char* var_name, int value);
    void set_uniform(const char* var_name, unsigned int value);

  private:
    GLuint m_id;
    std::vector<std::shared_ptr<Shader>> m_attached_shaders;
};

#endif // RT_SHADER_PROGRAM_H