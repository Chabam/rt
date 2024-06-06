#include "rt/utils/image.hpp"
#include "glad/gl.h"
#include <rt/graphics/gl/texture.hpp>
#include <memory>

namespace rt
{

Texture::Texture(const std::shared_ptr<Image>& image)
    : m_id{}
    , m_image(image)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    glTextureStorage2D(m_id, 1, GL_RGB8, m_image->m_width, m_image->m_height);

    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTextureSubImage2D(m_id, 0, 0, 0, m_image->m_width, m_image->m_height, GL_RGB, GL_UNSIGNED_BYTE,
                        m_image->m_pixels.get());
    glGenerateMipmap(m_id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
    glBindTextureUnit(0, m_id);
}

void Texture::unbind() const
{
    glBindTextureUnit(0, 0);
}

} // namespace rt