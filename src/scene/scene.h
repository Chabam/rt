#pragma once
#include <object/light.h>
#include <object/object3d.h>
#include <vector>

class Scene
{
  public:
    Scene();
    Scene(const Scene& other);
    Scene& operator=(const Scene& other);

    void swap(Scene& other);

    void render();
    bool empty();
    void changeProjectionMatrix(glm::mat4 matrix);
    void addObject(const std::shared_ptr<Object3d>& object);
    void setLight(const Light& light);
    const std::vector<std::shared_ptr<Object3d>>& getObjects();

  private:
    std::vector<std::shared_ptr<Object3d>> m_objects;
    Light m_light;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};