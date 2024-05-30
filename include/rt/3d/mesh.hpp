#ifndef RT_MESH_H
#define RT_MESH_H

#include <rt/graphics/gl/vertex.hpp>

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

class Buffer;
class Camera;
class Light;
class Material;
class Triangle;
class Shader;

class Mesh
{
  public:
    Mesh(const Material& material);
    virtual ~Mesh();

    virtual uint32_t getTriangleCount() const = 0;

    void render(const Camera& camera, const Light& light) const;

    void setModel(const glm::mat4& trans);
    const glm::mat4& getModel() const;

  protected:
    std::unique_ptr<Buffer> m_buffer;
    const Material& m_material;
    glm::mat4 m_model;
    glm::mat3 m_normalMatrix;
};

#endif // RT_MESH_H