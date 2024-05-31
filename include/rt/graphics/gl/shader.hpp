#ifndef RT_SHADER_H
#define RT_SHADER_H

#include <glad/gl.h>
#include <optional>
#include <string>

class Shader
{
  public:
    enum class Type
    {
        Vertex,
        Fragment
    };

    Shader(Type type, const char* source);
    ~Shader();

    Shader(Shader&&);
    Shader& operator=(Shader&&);

    Shader(Shader&) = delete;
    Shader& operator=(Shader&) = delete;

    GLuint getId() const { return m_id; }

    static std::optional<Shader> try_compile(Type type, const char* source) noexcept;

  private:
    GLuint m_id;
};

#endif // RT_SHADER_H