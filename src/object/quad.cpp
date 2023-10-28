#include "object/quad.h"

Quad::Quad(const Vertice &p1, const Vertice &p2, const Vertice &p3, const Vertice &p4)
    : Mesh({Triangle(p1, p2, p3), Triangle(p1, p3, p4)}), m_p{p1, p2, p3, p4}
{
}

Quad::Quad(const Quad &other) : Mesh({Triangle(other.m_p[0], other.m_p[1], other.m_p[2]), Triangle(other.m_p[0], other.m_p[2], other.m_p[3])}), m_p(other.m_p)
{
}

Quad &Quad::operator=(const Quad &other)
{
    m_p = other.m_p;

    return *this;
}