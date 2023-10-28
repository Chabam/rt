#include "object/color.h"

const Color::Normalized Color::normalize(RGB color)
{
    return {
        color.r / 255.f,
        color.g / 255.f,
        color.b / 255.f,
        color.a / 255.f,
    };
}