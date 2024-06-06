#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include <memory>

namespace rt
{

class ShaderProgram;
class Camera;
class Texture;
struct Light;
class Mesh;

class Material
{
  public:
    Material(const std::shared_ptr<ShaderProgram>& shader);
    virtual ~Material();

    void forward_uniforms(const Mesh& mesh, const Camera& camera, const Light& light) const;

  protected:
    virtual void forward_properties_uniforms() const = 0;

    const std::shared_ptr<ShaderProgram>& m_shader;
};

} // namespace rt

#endif // RT_MATERIAL_H