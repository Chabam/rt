#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include <rt/utils/image.hpp>

#include <glad/gl.h>
#include <memory>

namespace rt
{

class Texture
{
  public:
    Texture(const std::shared_ptr<Image>& image);
    ~Texture();

    void bind() const;
    void unbind() const;

  private:
    GLuint m_id;
    std::shared_ptr<Image> m_image;
};

} // namespace rt

#endif // RT_TEXTURE_H