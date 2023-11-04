#include <glContext/buffer.h>
#include <glContext/shader.h>
#include <glContext/window.h>
#include <glm/gtx/transform.hpp>
#include <scene/scene.h>
class Engine
{
  public:
    Engine();

    static void init();
    void setScene(const Scene& scene);
    void start();

  private:
    Window m_window;
    Scene m_scene;
    uint8_t m_fps;

    void handleKeyPress(int keyCode);
    void handleResize(int width, int height);
    static void handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam);
};