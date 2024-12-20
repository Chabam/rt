#ifndef RT_SHADER_H
#define RT_SHADER_H

#include <rt/utils/logger.hpp>

#include <glad/gl.h>
#include <optional>
#include <string>

namespace rt
{

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

    GLuint get_id() const { return m_id; }

    static std::optional<Shader> try_compile(Type type, const char* source) noexcept;

  private:
    GLuint m_id;
    Type m_type;
    Logger m_logger{"Shader"};
};

} // namespace rt

#endif // RT_SHADER_H