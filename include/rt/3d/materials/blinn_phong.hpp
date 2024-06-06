#ifndef RT_BLINN_PHONG_H
#define RT_BLINN_PHONG_H

#include <rt/3d/material.hpp>

#include <glm/ext/vector_float3.hpp>

namespace rt
{

class BlinnPhong : public Material
{
  public:
    struct Properties
    {
        glm::vec3 m_color = glm::vec3(1.f);
        float m_specular = 0.f;
        unsigned int m_shininess = 1;
        bool m_emitsLight = false;
    };

    BlinnPhong(const Properties& properties);

    glm::vec3 m_color;
    float m_specular;
    unsigned int m_shininess;
    bool m_emitsLight;

  private:
    virtual void forward_properties_uniforms() const override;
};

} // namespace rt

#endif // RT_BLINN_PHONG_H