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

    struct MouseInfo
    {
        double m_lastX;
        double m_lastY;
        bool m_pressed;
    } m_mouseInfo;

    void handleKeyPress(int keyCode);
    void handleResize(int width, int height);
    void handleMousePositionChanged(double xPos, double yPos);
    void handleMouseButtonPressed(int key, int action, int mod);

    static void handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam);
};