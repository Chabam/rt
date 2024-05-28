#include <rt/graphics/gl/shader.hpp>
#include <rt/graphics/gl/shaderProgram.hpp>
#include <rt/logger/logger.hpp>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderProgram::ShaderProgram()
    : m_id(glCreateProgram())
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

void ShaderProgram::attachShader(const std::shared_ptr<Shader>& shader)
{
    m_attachedShaders.push_back(shader);
}

void ShaderProgram::link()
{
    for (const auto& shader : m_attachedShaders)
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

void ShaderProgram::setMatrixUniform(const char* varName, const glm::mat4& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setMatrixUniform(const char* varName, const glm::mat3& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setVectorUniform(const char* varName, const glm::vec4& vector)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform4f(uniformLocation, vector.r, vector.g, vector.b, vector.a);
}

void ShaderProgram::setVectorUniform(const char* varName, const glm::vec3& vector)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform3f(uniformLocation, vector.r, vector.g, vector.b);
}

void ShaderProgram::setFloatUniform(const char* varName, float value)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::setIntUniform(const char* varName, int value)
{
    const int uniformLocation = glGetUniformLocation(m_id, varName);
    glUniform1i(uniformLocation, value);
}