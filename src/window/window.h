#pragma once
#include <functional>
#include <memory>

class Window
{
  public:
    typedef std::function<void(int)> KeyPressCallback;
    typedef std::function<void(int, int)> WindowResizeCallback;
    typedef std::function<void(int, int, int)> MouseButtonPressedCallback;
    typedef std::function<void(double, double)> MousePositionChangedCallback;

    Window();
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();

    void setToClose();
    bool shouldClose();
    void setSize(int width, int height);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setResizeCallback(WindowResizeCallback cb);
    void setKeyPressCallback(KeyPressCallback cb);
    void setMouseButtonPressedCallback(MouseButtonPressedCallback cb);
    void setMousePositionChangedCallback(MousePositionChangedCallback cb);
    void swapBuffers();

  private:
    unsigned int m_width;
    unsigned int m_height;
    const char* m_title;
    struct Impl;
    std::unique_ptr<Impl> m_impl;

    WindowResizeCallback m_windowResizeCallback;
    KeyPressCallback m_windowKeyPressCallback;
    MouseButtonPressedCallback m_mouseButtonPressedCallback;
    MousePositionChangedCallback m_mousePositionChangedCallback;
};