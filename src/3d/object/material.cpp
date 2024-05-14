#include <rt/3d/material.hpp>

Material::Material(const glm::vec3& color, float specular, int shininess)
    : m_color(color)
    , m_specular(specular)
    , m_shininess(shininess)
{
}

Material::Material(const Material& other)
    : m_color(other.m_color)
    , m_specular(other.m_specular)
    , m_shininess(other.m_shininess)
{
}

Material& Material::operator=(const Material& other)
{
    m_color = other.m_color;
    m_specular = other.m_specular;
    m_shininess = other.m_shininess;

    return *this;
}