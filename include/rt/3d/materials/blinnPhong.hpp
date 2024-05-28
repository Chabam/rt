#ifndef RT_BLINN_PHONG_H
#define RT_BLINN_PHONG_H

#include <rt/3d/material.hpp>

class BlinnPhong : public Material
{
  public:
    struct Properties
    {
        glm::vec3 m_color = glm::vec3(1.f);
        float m_specular = 0.f;
        uint32_t m_shininess = 1;
        bool m_emitsLight = false;
    };

    BlinnPhong(const Properties& properties);

    glm::vec3 m_color;
    float m_specular;
    uint32_t m_shininess;
    bool m_emitsLight;

  private:
    virtual void forwardPropertiesUniforms() const override;
};

#endif // RT_BLINN_PHONG_H