#ifndef RT_SCENE_H
#define RT_SCENE_H

#include <rt/3d/camera/camera.hpp>
#include <rt/3d/light/light.hpp>

#include <memory>
#include <vector>

namespace rt
{

class Mesh;

class Scene
{
  public:
    Scene();
    Scene(const Scene& other);
    Scene& operator=(const Scene& other);

    void render();
    bool empty();
    void add_mesh(const std::shared_ptr<Mesh>& mesh);
    void set_light(const Light& light);
    void set_camera(const Camera& camera);
    Camera& get_camera();
    const Camera& get_camera() const;
    const std::vector<std::shared_ptr<Mesh>>& get_meshes() const;

  private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    Camera m_camera;
    Light m_light;
};

} // namespace rt

#endif // RT_SCENE_H