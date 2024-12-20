#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include <rt/utils/image.hpp>

#include <glad/gl.h>
#include <memory>
#include <optional>

namespace rt
{

class Texture
{
  public:
    Texture(const std::shared_ptr<Image>& image, const std::optional<std::shared_ptr<Image>>& normal_map = {});
    ~Texture();

    void bind() const;
    void unbind() const;

    bool has_normal_map() const;

  private:
    GLuint m_id;
    GLuint m_normal_id;
    std::shared_ptr<Image> m_image;
    std::optional<std::shared_ptr<Image>> m_normal_map;
};

} // namespace rt

#endif // RT_TEXTURE_H
