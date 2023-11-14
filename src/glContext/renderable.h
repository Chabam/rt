#pragma once
#include <glm/mat4x4.hpp>
#include <object/light/light.h>

class Renderable
{
  public:
    virtual void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPos,
                        const Light& light) const = 0;
};