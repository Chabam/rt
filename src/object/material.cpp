#include "object/material.h"

Material::Material(const glm::vec4& color, float diffuse, float specular)
    : m_color(color), m_diffuse(diffuse), m_specular(specular)
{
}

Material::Material(const Material &other)
    : m_color(other.m_color), m_diffuse(other.m_diffuse), m_specular(other.m_specular)
{
}

Material &Material::operator=(const Material &other)
{
    m_color = other.m_color;
    m_diffuse = other.m_diffuse;
    m_specular = other.m_specular;

	return *this;
}