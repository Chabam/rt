#include "glContext/buffer.h"
#include "glContext/shader.h"
#include "glContext/window.h"
#include "object/mesh.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
class Engine
{
  public:
    class RenderTarget
    {
      public:
        Mesh m_mesh;
        Buffer m_buffer;

        RenderTarget(const Mesh &mesh, Buffer &&buffer);
    };

    Engine(const Shader &shader, const Window &window = Window(1920, 1080));

    void init();
    void setMeshes(const std::vector<Mesh> &meshes);
    void start();

  private:
    Window m_window;
    Shader m_shader;
    std::vector<RenderTarget> m_renderTargets;
    uint8_t m_fps;

    void render();
    static void handleKeyPress(Engine *engine, int keyCode);
    static void handleResize(Engine *engine, int width, int height);
    static void handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar *message, const void *userParam);

    const glm::mat4 VIEW_MATRIX = glm::lookAt(glm::vec3(0, 0, 4), // Camera is at (4,3,3), in World Space
                                              glm::vec3(0, 0, 0), // and looks at the origin
                                              glm::vec3(0, -1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 PROJECTION_MATRIX = glm::perspective(glm::radians(90.f), 16 / 9.f, 0.1f, 100.0f);
};