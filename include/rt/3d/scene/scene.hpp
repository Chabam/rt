#pragma once
#include <rt/3d/camera/camera.hpp>
#include <rt/3d/light/light.hpp>
#include <rt/graphics/gl/renderable.hpp>

#include <memory>
#include <vector>


class Scene
{
  public:
    Scene();
    Scene(const Scene& other);
    Scene& operator=(const Scene& other);

    void render();
    bool empty();
    void addObject(const std::shared_ptr<Renderable>& object);
    void setLight(const Light& light);
    void setCamera(const Camera& camera);
    Camera& getCamera();
    const Camera& getCamera() const;
    const std::vector<std::shared_ptr<Renderable>>& getObjects();

  private:
    std::vector<std::shared_ptr<Renderable>> m_objects;
    Camera m_camera;
    Light m_light;
};