#include <rt/graphics/gl/verticeBufferData.hpp>

#include <glad/gl.h>

VerticeBufferData::operator FloatValues() const
{
    return {m_position.x, m_position.y, m_position.z, m_normal.x, m_normal.y, m_normal.z};
}