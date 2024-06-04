#ifndef RT_IMAGE_H
#define RT_IMAGE_H

#include <glm/vec3.hpp>
#include <stddef.h>
#include <vector>

struct Image
{
    size_t m_width;
    size_t m_height;

    std::vector<char> m_pixels;
};

#endif // RT_IMAGE_H