#pragma once
#include <object/camera/camera.h>
#include <object/light/light.h>
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
    void addObject(const std::shared_ptr<Object3d>& object);
    void setLight(const Light& light);
    void setCamera(const Camera& camera);
    Camera& getCamera();
    const Camera& getCamera() const;
    const std::vector<std::shared_ptr<Object3d>>& getObjects();

  private:
    std::vector<std::shared_ptr<Object3d>> m_objects;
    Camera m_camera;
    Light m_light;
};