#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

class Shader;
class Buffer;
class Material;
class Light;

class Object3d
{
  public:
    Object3d(const Material& material);
    virtual ~Object3d();

    void setModel(const glm::mat4& trans);
    const glm::mat4& getModel() const;
    virtual void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPos,
                        const Light& light) = 0;

  protected:
    std::unique_ptr<Buffer> m_buffer;
    const Material& m_material;
    glm::mat4 m_model;
    glm::mat3 m_normalMatrix;
};

#endif // RT_OBJECT_H