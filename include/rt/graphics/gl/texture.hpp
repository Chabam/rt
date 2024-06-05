#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include <rt/utils/image.hpp>

#include <glad/gl.h>

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

#endif // RT_TEXTURE_H