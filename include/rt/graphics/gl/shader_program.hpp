#ifndef RT_SHADER_PROGRAM_H
#define RT_SHADER_PROGRAM_H

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/ext/vector_float3.hpp"
#include <rt/utils/logger.hpp>

#include <glad/gl.h>
#include <memory>
#include <vector>

namespace rt
{

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
    Logger m_logger{"ShaderProgram"};
};

} // namespace rt

#endif // RT_SHADER_PROGRAM_H