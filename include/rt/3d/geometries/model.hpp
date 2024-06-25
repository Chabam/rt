#ifndef RT_CUSTOM_MODEL_H
#define RT_CUSTOM_MODEL_H

#include <rt/3d/geometries/geometry.hpp>

#include <memory>

namespace rt
{

class Model final : public Geometry
{
  public:
    Model(const std::string& obj_file_content);

    std::span<const Vertex> get_vertices() const override;
    std::span<const unsigned short> get_indices() const override;

  private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned short> m_indices;
};

} // namespace rt

#endif // RT_CUSTOM_MODEL_H