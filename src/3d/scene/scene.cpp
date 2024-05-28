#include <rt/3d/mesh.hpp>
#include <rt/3d/scene/scene.hpp>


Scene::Scene()
    : m_meshes()
    , m_light()
    , m_camera()
{
}

Scene::Scene(const Scene& other)
    : m_meshes(other.m_meshes)
    , m_light(other.m_light)
{
}

Scene& Scene::operator=(const Scene& other)
{
    m_meshes = other.m_meshes;
    m_light = other.m_light;

    return *this;
}

void Scene::render()
{
    for (const auto& mesh : m_meshes)
    {
        mesh->render(m_camera, m_light);
    }
}

bool Scene::empty()
{
    return m_meshes.empty();
}

void Scene::addMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_meshes.push_back(mesh);
}

void Scene::setLight(const Light& light)
{
    m_light = light;
}

void Scene::setCamera(const Camera& camera)
{
    m_camera = camera;
}

Camera& Scene::getCamera()
{
    return m_camera;
}

const Camera& Scene::getCamera() const
{
    return m_camera;
}

const std::vector<std::shared_ptr<Mesh>>& Scene::getMeshes()
{
    return m_meshes;
}