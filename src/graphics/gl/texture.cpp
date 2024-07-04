#include "rt/utils/image.hpp"
#include "glad/gl.h"
#include <rt/graphics/gl/texture.hpp>
#include <memory>

namespace rt
{

void create_gl_texture(GLuint& id, const std::shared_ptr<Image>& image)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &id);

    glTextureStorage2D(id, 1, GL_RGB8, image->m_width, image->m_height);

    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTextureSubImage2D(id, 0, 0, 0, image->m_width, image->m_height, GL_RGB, GL_UNSIGNED_BYTE,
                        image->m_pixels.get());
    glGenerateMipmap(id);
}

Texture::Texture(const std::shared_ptr<Image>& image, const std::shared_ptr<Image>& normal_map)
    : m_id{}
    , m_normal_id{}
    , m_image{image}
    , m_normal_map{normal_map}
{
    create_gl_texture(m_id, m_image);
    create_gl_texture(m_normal_id, m_normal_map);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
    glBindTextureUnit(0, m_id);
    if (has_normal_map())
        glBindTextureUnit(1, m_normal_id);
}

void Texture::unbind() const
{
    glBindTextureUnit(0, 0);
    if (has_normal_map())
        glBindTextureUnit(1, 0);
}

bool Texture::has_normal_map() const
{
    return static_cast<bool>(m_normal_map);
}

} // namespace rt