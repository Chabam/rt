#ifndef RT_IMAGE_H
#define RT_IMAGE_H

#include <functional>
#include <memory>
#include <stb_image.h>

namespace rt
{

struct Image
{
    Image(const char* path);

    Image(Image&& other);
    Image& operator=(Image&& other);

    const char* m_path;
    int m_width;
    int m_height;
    int m_channels;

    std::unique_ptr<stbi_uc, std::function<void(void*)>> m_pixels;
};

} // namespace rt

#endif // RT_IMAGE_H