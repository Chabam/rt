#include "glContext/shader.h"
#include "glContext/window.h"
#include "logger/logger.h"
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vertPath, const char *fragPath)
    : m_vertPath(vertPath)
    , m_fragPath(fragPath)
    , m_vertUid()
    , m_fragUid()
    , m_programUid()
{
}

Shader::~Shader()
{
}

const std::string Shader::readFromFile(const char *relativePath)
{
    std::filesystem::path path = std::filesystem::current_path().append(relativePath);
    std::ifstream file = std::ifstream(path);
    std::ostringstream fileContent;
    std::string line;

    if (!file.is_open())
    {
        std::string error_message = std::string("File not found: ") + path.u8string() + "\n";
        throw std::runtime_error(error_message.c_str());
    }

    while (std::getline(file, line))
    {
        fileContent << line << "\n";
    }

    return fileContent.str();
}

void Shader::compileShaderSource(GLuint &shaderUid, GLenum type, const GLchar *source)
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
        for (auto &character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
}

void Shader::load()
{
    // Compiling shaders

    compileShaderSource(m_vertUid, GL_VERTEX_SHADER, readFromFile(m_vertPath).c_str());
    LOG_INFO("Vertex shader compiled");

    compileShaderSource(m_fragUid, GL_FRAGMENT_SHADER, readFromFile(m_fragPath).c_str());
    LOG_INFO("Fragment shader compiled");

    m_programUid = glCreateProgram();

    glAttachShader(m_programUid, m_vertUid);
    glAttachShader(m_programUid, m_fragUid);

    glLinkProgram(m_programUid);

    GLint isLinked = 0;
    glGetProgramiv(m_programUid, GL_LINK_STATUS, (int *)&isLinked);
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
        for (auto &character : infoLog)
        {
            out << character;
        }

        throw std::runtime_error(out.str());
    }
    LOG_INFO("Program linked");

    glDetachShader(m_programUid, m_vertUid);
    glDetachShader(m_programUid, m_fragUid);
}

void Shader::bind() const
{
    glUseProgram(m_programUid);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniforms(const Material &material, const glm::mat4 &model, const glm::mat4 &view,
                         const glm::mat4 &projection)
{
    int projectionMatrixLocation = glGetUniformLocation(m_programUid, "projection");
    int viewMatrixLocation = glGetUniformLocation(m_programUid, "view");
    int modelMatrixLocation = glGetUniformLocation(m_programUid, "model");
    int colorLocation = glGetUniformLocation(m_programUid, "color");

    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform4f(colorLocation, material.m_color.r, material.m_color.g, material.m_color.b, material.m_color.a);
}

void Shader::init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Could not initialize GLEW!");

    load();
}

void Shader::reload()
{
    try
    {
        load();
    }
    catch (std::runtime_error e)
    {
        LOG_ERROR("Failed reloading the shaders: " << e.what());
        LOG_INFO("Keeping previous version!");
    }
}
