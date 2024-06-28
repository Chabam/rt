#ifndef RT_GEOMETRY_H
#define RT_GEOMETRY_H

#include <rt/graphics/gl/vertex.hpp>

#include <span>

namespace rt
{

class Geometry
{
  public:
    virtual ~Geometry() = default;
    virtual std::span<const Vertex> get_vertices() const = 0;
    virtual std::span<const unsigned int> get_indices() const = 0;
};

} // namespace rt

#endif // RT_GEOMETRY_H