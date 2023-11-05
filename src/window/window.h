#include <exception>
#include <functional>
#include <memory>
#include <vector>

class Window
{
  public:
    typedef std::function<void(int)> KeyPressCallback;
    typedef std::function<void(int, int)> WindowResizeCallback;

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
    void swapBuffers();

  private:
    unsigned int m_width;
    unsigned int m_height;
    const char* m_title;
    struct Impl;
    std::unique_ptr<Impl> m_impl;

    WindowResizeCallback m_windowResizeCallback;
    KeyPressCallback m_windowKeyPressCallback;
};