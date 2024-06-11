#ifndef RT_ENGINE_H
#define RT_ENGINE_H

#include <rt/3d/scene.hpp>
#include <rt/graphics/window/window.hpp>
#include <rt/utils/logger.hpp>

#include <chrono>
#include <glad/gl.h>
#include <memory>

namespace rt
{

class EngineComponent;

class Engine
{
  public:
    Engine();

    void render(Window& window, Scene& scene);

    void register_engine_component(const std::shared_ptr<EngineComponent>& engine_component);

  private:
    unsigned int m_target_fps;
    unsigned long long m_frame_count;

    std::vector<std::shared_ptr<EngineComponent>> m_engine_components;

    Logger m_logger{"engine"};

    static void handle_gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* user_param);
};

} // namespace rt

#endif // RT_ENGINE_H