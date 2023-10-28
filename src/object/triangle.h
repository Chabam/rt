#pragma once
#include "object/vertice.h"
#include <array>

class Triangle
{
  public:
    Triangle(const Vertice &p1, const Vertice &p2, const Vertice &p3);
    Triangle(const Triangle &other);
    Triangle(const std::array<Vertice, 3> &other);
    Triangle& operator=(const Triangle &other);

    std::array<Vertice, 3> m_p;
};