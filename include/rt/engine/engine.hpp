#pragma once

#include <rt/3d/scene/scene.hpp>
#include <rt/graphics/window/window.hpp>

#include <chrono>
#include <glad/gl.h>


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
    std::chrono::duration<double> m_frameTime;

    struct MouseInfo
    {
        double m_lastX;
        double m_lastY;
        bool m_pressed;
    } m_mouseInfo;

    struct KeyboardInfo
    {
        bool m_forwardKeyPressed;
        bool m_backwardKeyPressed;
        bool m_leftKeyPressed;
        bool m_rightKeyPressed;
        bool m_upKeyPressed;
        bool m_downKeyPressed;

    } m_keyboardInfo;

    void handleKeyPress(int keyCode, int action);
    void handleResize(int width, int height);
    void handleMousePositionChanged(double xPos, double yPos);
    void handleMouseButtonPressed(int key, int action, int mod);

    void processInputs();

    static void handleGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam);
};