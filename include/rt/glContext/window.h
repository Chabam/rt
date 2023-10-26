#pragma once

#include <GLFW/glfw3.h>
#include <exception>
#include <functional>
#include <glad/gl.h>
#include <vector>

class Window
{
  public:
    typedef std::function<void(int)> KeyPressCallback;
    typedef std::function<void(int, int)> WindowResizeCallback;

    Window(int width, int height, const char *title = "rt-engine");
    ~Window();

    void init();
    void setToClose();
    bool shouldClose();
    void setSize(int width, int height);
    void setResizeCallback(WindowResizeCallback cb);
    void setKeyPressCallback(KeyPressCallback cb);
    void swapBuffers();
    float getAspectRatio() const;

  private:
    int m_width;
    int m_height;
    const char *m_title;
    GLFWwindow *m_impl;

    WindowResizeCallback m_windowResizeCallback = nullptr;
    KeyPressCallback m_windowKeyPressCallback = nullptr;

    static void keyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods);
    static void resizeCallback(GLFWwindow *glfwWindow, int with, int height);
};