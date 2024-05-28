#ifndef RT_SCENE_H
#define RT_SCENE_H

#include <rt/3d/camera/camera.hpp>
#include <rt/3d/light/light.hpp>

#include <memory>
#include <vector>

class Mesh;

class Scene
{
  public:
    Scene();
    Scene(const Scene& other);
    Scene& operator=(const Scene& other);

    void render();
    bool empty();
    void addMesh(const std::shared_ptr<Mesh>& mesh);
    void setLight(const Light& light);
    void setCamera(const Camera& camera);
    Camera& getCamera();
    const Camera& getCamera() const;
    const std::vector<std::shared_ptr<Mesh>>& getMeshes();

  private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    Camera m_camera;
    Light m_light;
};

#endif // RT_SCENE_H