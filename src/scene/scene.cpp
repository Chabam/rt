#include "scene.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>

const auto DEFAULT_VIEW_MATRIX = glm::lookAt(glm::vec3(0, 0, 4),   // Camera is at (4,3,3), in World Space
                                             glm::vec3(0, 0, 0),   // and looks at the origin
                                             glm::vec3(0, -1, 0)); // Head is up (set to 0,-1,0 to look upside-down)
const auto DEFAULT_PROJECTION_MATRIX = glm::perspective(glm::radians(90.f), 16 / 9.f, 0.1f, 100.0f);

Scene::Scene()
    : m_objects()
    , m_light()
    , m_viewMatrix(DEFAULT_VIEW_MATRIX)
    , m_projectionMatrix(DEFAULT_PROJECTION_MATRIX)
{
}

Scene::Scene(const Scene& other)
    : m_objects(other.m_objects)
    , m_light(other.m_light)
    , m_viewMatrix(other.m_viewMatrix)
    , m_projectionMatrix(other.m_projectionMatrix)
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
    std::swap(other.m_viewMatrix, m_viewMatrix);
    std::swap(other.m_projectionMatrix, m_projectionMatrix);
    std::swap(other.m_light, m_light);
}

void Scene::render()
{
    for (const auto& object : m_objects)
    {
        object->render(m_viewMatrix, m_projectionMatrix, m_light);
    }
}

bool Scene::empty()
{
    return m_objects.empty();
}

void Scene::changeProjectionMatrix(glm::mat4 matrix)
{
    m_projectionMatrix = matrix;
}

void Scene::addObject(const std::shared_ptr<Object3d>& object)
{
    m_objects.push_back(object);
}

void Scene::setLight(const Light& light)
{
    m_light = light;
}

const std::vector<std::shared_ptr<Object3d>>& Scene::getObjects()
{
    return m_objects;
}