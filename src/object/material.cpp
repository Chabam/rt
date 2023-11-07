#include "material.h"

Material::Material(const glm::vec3& color, float specular)
    : m_color(color)
    , m_specular(specular)
{
}

Material::Material(const Material& other)
    : m_color(other.m_color)
    , m_specular(other.m_specular)
{
}

Material& Material::operator=(const Material& other)
{
    m_color = other.m_color;
    m_specular = other.m_specular;

    return *this;
}