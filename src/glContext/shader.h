#pragma once
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <object/material.h>
#include <sstream>
#include <string>

class Shader
{
  public:
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();
    void init();
    void reload();
    void bind() const;
    void unbind() const;
    void setUniforms(const Material& material, const glm::mat4& model, const glm::mat4& view,
                     const glm::mat4& projection);

  private:
    const char* m_vertPath;
    const char* m_fragPath;
    GLuint m_vertUid;
    GLuint m_fragUid;
    GLuint m_programUid;

    void load();

    static const std::string readFromFile(const char* relativePath);
    static void compileShaderSource(GLuint& shaderUid, GLenum type, const GLchar* source);
};