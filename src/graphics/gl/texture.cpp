#include <rt/graphics/gl/texture.hpp>

Texture::Texture(const Image& image)
    : m_id{}
    , m_image(image)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTextureStorage2D(m_id, 0, GL_RGB, m_image.m_width, m_image.m_height);

    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTextureSubImage2D(m_id, 0, 0, 0, m_image.m_width, m_image.m_height, GL_RGB, GL_UNSIGNED_BYTE,
                        m_image.m_pixels.data());
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}