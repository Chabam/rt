#pragma once
#include "object/mesh.h"
#include "object/triangle.h"
#include "object/vertice.h"
#include <array>

class Quad : public Mesh
{
  public:
    Quad(const Vertice &p1, const Vertice &p2, const Vertice &p3, const Vertice &p4);
    Quad(const Quad &other);
    Quad &operator=(const Quad &other);

	std::array<Vertice, 4> m_p;
};