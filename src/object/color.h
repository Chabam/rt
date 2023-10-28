#pragma once
#include <array>

namespace Color
{

struct RGB
{
    int r, g, b, a;
};

typedef std::array<float, 4> Normalized;

const Normalized normalize(RGB color);

} // namespace Color