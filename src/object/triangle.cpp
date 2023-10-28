#include "object/triangle.h"

Triangle::Triangle(const Vertice &p1, const Vertice &p2, const Vertice &p3) : m_p({p1, p2, p3})
{
}

Triangle::Triangle(const Triangle& other): m_p(other.m_p)
{
}

Triangle::Triangle(const std::array<Vertice, 3> &other): m_p(other)
{
}

Triangle& Triangle::operator=(const Triangle& other)
{
	m_p = other.m_p;

	return *this;
}