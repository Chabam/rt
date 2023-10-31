#include <glContext/buffer.h>
#include <glContext/shader.h>
#include <glContext/window.h>
#include <glm/gtx/transform.hpp>
#include <scene/scene.h>
class Engine
{
  public:
    Engine(const Window& window = Window(1920, 1080));

    void init();
    void setScene(const Scene& scene);
    void start();

  private:
    Window m_window;
    Scene m_scene;
    uint8_t m_fps;

    static void handleKeyPress(Engine* engine, int keyCode);
    static void handleResize(Engine* engine, int width, int height);
    static void handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam);
};