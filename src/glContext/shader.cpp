#include "shader.h"

#include <glad/glad.h>

#include <filesystem>
#include <glm/gtc/type_ptr.hpp>
#include <utils/logger.h>
#include <window/window.h>

Shader::Shader(const char* vertSrc, const char* fragSrc)
    : m_vertUid()
    , m_fragUid()
    , m_programUid()
{
    compileShaderSource(m_vertUid, GL_VERTEX_SHADER, vertSrc);
    Logger::debug("Vertex shader compiled");

    compileShaderSource(m_fragUid, GL_FRAGMENT_SHADER, fragSrc);
    Logger::debug("Fragment shader compiled");

    m_programUid = glCreateProgram();

    glAttachShader(m_programUid, m_vertUid);
    glAttachShader(m_programUid, m_fragUid);

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

        glDeleteShader(m_vertUid);
        glDeleteShader(m_fragUid);

        std::ostringstream out;
        out << "Linking error: ";
        for (auto& character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
    Logger::debug("Program linked");

    glDetachShader(m_programUid, m_vertUid);
    glDetachShader(m_programUid, m_fragUid);
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

void Shader::bind() const
{
    glUseProgram(m_programUid);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setMatrixUniform(const char* varName, const glm::mat4& matrix)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVectorUniform(const char* varName, const glm::vec4& vector)
{
    const int uniformLocation = glGetUniformLocation(m_programUid, varName);
    glUniform4f(uniformLocation, vector.r, vector.g, vector.b, vector.a);
}
