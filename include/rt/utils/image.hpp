#ifndef RT_IMAGE_H
#define RT_IMAGE_H

#include <stddef.h>
#include <vector>

struct Pixel
{
    char r;
    char g;
    char b;
};

struct Image
{
    size_t m_width;
    size_t m_height;

    std::vector<Pixel> m_pixels;
};

#endif // RT_IMAGE_H