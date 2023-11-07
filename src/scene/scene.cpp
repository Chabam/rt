#include "scene.h"

Scene::Scene()
    : m_objects()
    , m_light()
    , m_camera()
{
}

Scene::Scene(const Scene& other)
    : m_objects(other.m_objects)
    , m_light(other.m_light)
{
}

Scene& Scene::operator=(const Scene& other)
{
    Scene(other).swap(*this);

    return *this;
}

void Scene::swap(Scene& other)
{
    std::swap(other.m_objects, m_objects);
    std::swap(other.m_light, m_light);
}

void Scene::render()
{
    for (const auto& object : m_objects)
    {
        object->render(m_camera.getViewMatrix(), m_camera.getProjectionMatrix(), m_light);
    }
}

bool Scene::empty()
{
    return m_objects.empty();
}

void Scene::addObject(const std::shared_ptr<Object3d>& object)
{
    m_objects.push_back(object);
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

const std::vector<std::shared_ptr<Object3d>>& Scene::getObjects()
{
    return m_objects;
}