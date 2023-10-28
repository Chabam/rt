#include "object/cube.h"
#include "object/quad.h"

Cube::Cube(const Material &material) : Mesh({}, material)
{
    for (const Quad &quad : m_quads)
    {
        const auto &triangles = quad.getTriangles();
        m_triangles.insert(m_triangles.end(), triangles.begin(), triangles.end());
    }
    // clang-format on
}
