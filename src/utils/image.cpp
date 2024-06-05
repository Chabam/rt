#include <rt/utils/image.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const char* path)
    : m_path{path}
    , m_width{}
    , m_height{}
    , m_pixels{stbi_load(path, &m_width, &m_height, &m_channels, 0), stbi_image_free}
{
}

Image::Image(Image&& other)
    : m_path(std::move(other.m_path))
    , m_width(std::move(other.m_width))
    , m_height(std::move(other.m_height))
    , m_channels(std::move(other.m_channels))
    , m_pixels(std::move(other.m_pixels))
{
}

Image& Image::operator=(Image&& other)
{
    m_path = std::move(other.m_path);
    m_width = std::move(other.m_width);
    m_height = std::move(other.m_height);
    m_channels = std::move(other.m_channels);
    m_pixels = std::move(other.m_pixels);

    return *this;
}