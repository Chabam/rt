#include "shader.h"

#include <glad/glad.h>

#include <filesystem>
#include <glm/gtc/type_ptr.hpp>
#include <utils/logger.h>
#include <window/window.h>
#include <iostream>

Shader::Shader(const char* vertSrc, const char* fragSrc)
    : m_programUid()
{
    GLuint vertUid;
    compileShaderSource(vertUid, GL_VERTEX_SHADER, vertSrc);
    Logger::debug("Vertex shader compiled");

    GLuint fragUid;
    compileShaderSource(fragUid, GL_FRAGMENT_SHADER, fragSrc);
    Logger::debug("Fragment shader compiled");

    m_programUid = glCreateProgram();

    glAttachShader(m_programUid, vertUid);
    glAttachShader(m_programUid, fragUid);

    glLinkProgram(m_programUid);

    GLint isLinked = 0;
    glGetProgramiv(m_programUid, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_programUid, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_programUid, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(m_programUid);

        glDeleteShader(vertUid);
        glDeleteShader(fragUid);

        std::ostringstream out;
        out << "Linking error: ";
        for (auto& character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
    Logger::debug("Program linked");

    glDeleteShader(vertUid);
    glDeleteShader(fragUid);
}

Shader::~Shader()
{
    glDeleteProgram(m_programUid);
}

void Shader::compileShaderSource(GLuint& shaderUid, GLenum type, const GLchar* source)
{
    shaderUid = glCreateShader(type);
    glShaderSource(shaderUid, 1, &source, 0);
    glCompileShader(shaderUid);

    GLint isCompiled = 0;
    glGetShaderiv(shaderUid, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderUid, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shaderUid, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(shaderUid);

        std::ostringstream out;
        out << (type == GL_FRAGMENT_SHADER ? "Fragment" : "Vertex");
        out << " shader compilation failed :" << std::endl;
        for (auto& character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
}

void Shader::use() const
{
    glUseProgram(m_programUid);
}

void Shader::setMatrixUniform(const char* varName, const glm::mat4& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setMatrixUniform(const char* varName, const glm::mat3& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::setVectorUniform(const char* varName, const glm::vec4& vector)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniform4f(uniformLocation, vector.r, vector.g, vector.b, vector.a);
}

void Shader::setVectorUniform(const char* varName, const glm::vec3& vector)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniform3f(uniformLocation, vector.r, vector.g, vector.b);
}

void Shader::setFloatUniform(const char* varName, float value)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniform1f(uniformLocation, value);
}