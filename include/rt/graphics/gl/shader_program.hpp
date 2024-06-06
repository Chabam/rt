#ifndef RT_SHADER_PROGRAM_H
#define RT_SHADER_PROGRAM_H

#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"

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

    void set_uniform(const char* var_name, const glm::mat4& matrix) const;
    void set_uniform(const char* var_name, const glm::mat3& matrix) const;
    void set_uniform(const char* var_name, const glm::vec4& vector) const;
    void set_uniform(const char* var_name, const glm::vec3& vector) const;
    void set_uniform(const char* var_name, float value) const;
    void set_uniform(const char* var_name, int value) const;
    void set_uniform(const char* var_name, unsigned int value) const;

  private:
    GLuint m_id;
    std::vector<std::shared_ptr<Shader>> m_attached_shaders;
    Logger m_logger{"ShaderProgram"};
};

} // namespace rt

#endif // RT_SHADER_PROGRAM_H