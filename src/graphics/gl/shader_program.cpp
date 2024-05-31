#include <rt/graphics/gl/shader.hpp>
#include <rt/graphics/gl/shader_program.hpp>
#include <rt/utils/logger.hpp>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram()
    : m_id(glCreateProgram())
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

void ShaderProgram::attach_shader(const std::shared_ptr<Shader>& shader)
{
    m_attached_shaders.push_back(shader);
}

void ShaderProgram::link()
{
    for (const auto& shader : m_attached_shaders)
    {
        glAttachShader(m_id, shader->getId());
    }

    glLinkProgram(m_id);

    GLint isLinked = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);

        std::ostringstream out;
        out << "Linking error: ";
        for (auto& character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
    Logger::debug("Program linked");
}

void ShaderProgram::use() const
{
    glUseProgram(m_id);
}

void ShaderProgram::set_uniform(const char* varName, const glm::mat4& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::set_uniform(const char* varName, const glm::mat3& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::set_uniform(const char* varName, const glm::vec4& vector)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform4f(uniformLocation, vector.r, vector.g, vector.b, vector.a);
}

void ShaderProgram::set_uniform(const char* varName, const glm::vec3& vector)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform3f(uniformLocation, vector.r, vector.g, vector.b);
}

void ShaderProgram::set_uniform(const char* varName, float value)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::set_uniform(const char* varName, int value)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform1i(uniformLocation, value);
}

void ShaderProgram::set_uniform(const char* varName, unsigned int value)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform1ui(uniformLocation, value);
}