#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include <rt/utils/image.hpp>

#include <glad/gl.h>

class Texture
{
  public:
    Texture(const Image& image);
    ~Texture();

    GLuint get_id() const { return m_id; }

  private:
    GLuint m_id;
    Image m_image;
};

#endif // RT_TEXTURE_H