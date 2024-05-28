#include <rt/graphics/gl/shader.hpp>
#include <rt/logger/logger.hpp>

#include <filesystem>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLenum convertToGlEnum(Shader::Type type)
{
    switch (type)
    {
    case Shader::Type::Fragment:
        return GL_FRAGMENT_SHADER;
    case Shader::Type::Vertex:
        return GL_VERTEX_SHADER;
    default:
        throw std::runtime_error("Invalid shader type provided");
    }
}

const char* shaderTypeDisplayName(Shader::Type type)
{
    switch (type)
    {
    case Shader::Type::Fragment:
        return "Fragment";
    case Shader::Type::Vertex:
        return "Vertex";
    default:
        throw std::runtime_error("Invalid shader type provided");
    }
}

Shader::Shader(Type type, const char* source)
    : m_id(glCreateShader(convertToGlEnum(type)))
{
    glShaderSource(m_id, 1, &source, 0);
    glCompileShader(m_id);

    GLint isCompiled = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(m_id);

        std::ostringstream out;
        out << shaderTypeDisplayName(type);
        for (auto& character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

Shader::Shader(Shader&& other)
{
    m_id = std::move(other.m_id);
}

Shader& Shader::operator=(Shader&& other)
{
    m_id = std::move(other.m_id);

    return *this;
}

std::optional<Shader> Shader::tryCompile(Type type, const char* source) noexcept
{
    std::optional<Shader> shaderOutput;
    try
    {
        shaderOutput = Shader{type, source};
        Logger::debug(shaderTypeDisplayName(type)) << " shader compiled with success";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Shader compilation failed:\n" << e.what() << '\n';
    }

    return shaderOutput;
}