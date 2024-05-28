#ifndef RT_MESH_H
#define RT_MESH_H

#include <rt/3d/object.hpp>

#include <glm/glm.hpp>
#include <ranges>
#include <vector>

class Triangle;
class Light;

class Mesh : public Object3d
{
  public:
    Mesh(const Material& material);

    virtual uint32_t getTriangleCount() const = 0;
    virtual std::vector<VerticeBufferData> getVerticeBufferData() const = 0;

    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPos,
                const Light& light);
};

#endif // RT_MESH_H