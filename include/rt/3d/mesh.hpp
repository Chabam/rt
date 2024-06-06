#ifndef RT_MESH_H
#define RT_MESH_H

#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

namespace rt
{

class Buffer;
class Camera;
struct Light;
class Material;
class Texture;
class Triangle;
class Shader;

class Mesh
{
  public:
    Mesh(const std::shared_ptr<Material>& material, const std::shared_ptr<Texture>& texture = {});
    virtual ~Mesh();

    Mesh(const Mesh& other);
    Mesh& operator=(const Mesh& other);

    Mesh(Mesh&& other);
    Mesh& operator=(Mesh&& other);

    virtual unsigned int get_triangle_count() const = 0;

    void render(const Camera& camera, const Light& light) const;

    void set_model(const glm::mat4& trans);
    const glm::mat4& get_model() const;
    const glm::mat3& get_normal_matrix() const;
    bool has_texture() const;

  protected:
    std::unique_ptr<Buffer> m_buffer;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Texture> m_texture;
    glm::mat4 m_model;
    glm::mat3 m_normal_matrix;
};

} // namespace rt

#endif // RT_MESH_H