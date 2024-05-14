#pragma once
#include <array>
#include <glad/glad.h>
#include <glm/vec3.hpp>


struct VerticeBufferData
{
    glm::vec3 m_position;
    glm::vec3 m_normal;

    using FloatValues = std::array<GLfloat, decltype(m_position)::length() + decltype(m_normal)::length()>;
    operator FloatValues() const;
};