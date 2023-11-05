#pragma once

#include <glad/glad.h>
#include <scene/scene.h>
#include <window/window.h>

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
    unsigned int m_fps;

    void handleKeyPress(int keyCode);
    void handleResize(int width, int height);
    static void handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam);
};