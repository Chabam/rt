#include "scene.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>

const auto DEFAULT_VIEW_MATRIX = glm::lookAt(glm::vec3(0, 0, 4),   // Camera is at (4,3,3), in World Space
                                             glm::vec3(0, 0, 0),   // and looks at the origin
                                             glm::vec3(0, -1, 0)); // Head is up (set to 0,-1,0 to look upside-down)
const auto DEFAULT_PROJECTION_MATRIX = glm::perspective(glm::radians(90.f), 16 / 9.f, 0.1f, 100.0f);

Scene::Scene()
    : m_objects()
    , m_viewMatrix(DEFAULT_VIEW_MATRIX)
    , m_projectionMatrix(DEFAULT_PROJECTION_MATRIX)
{
}

Scene::Scene(const Scene& other)
    : m_objects(other.m_objects)
    , m_viewMatrix(other.m_viewMatrix)
    , m_projectionMatrix(other.m_projectionMatrix)
{
}

Scene& Scene::operator=(const Scene& other)
{
    m_objects = other.m_objects;
    m_viewMatrix = other.m_viewMatrix;
    m_projectionMatrix = other.m_projectionMatrix;

    return *this;
}

void Scene::render()
{
    static glm::vec4 BLACK = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(BLACK));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const Object3d* object : m_objects)
    {
        object->render(m_viewMatrix, m_projectionMatrix);
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

void Scene::addObject(const Object3d* object)
{
    m_objects.push_back(object);
}

const std::vector<const Object3d*>& Scene::getObjects()
{
    return m_objects;
}