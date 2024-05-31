#ifndef RT_WINDOW_H
#define RT_WINDOW_H

#include <functional>
#include <memory>

struct GLFWwindow;

class Window
{
  public:
    typedef std::function<void(int, int)> KeyPressCallback;
    typedef std::function<void(int, int)> WindowResizeCallback;
    typedef std::function<void(int, int, int)> MouseButtonPressedCallback;
    typedef std::function<void(double, double)> MousePositionChangedCallback;

    Window();
    Window(unsigned int width, unsigned int height, const char* title);

    void close();
    bool should_close();
    void set_title(const char* title);
    void set_size(int width, int height);
    unsigned int get_width() const;
    unsigned int get_height() const;
    void set_resize_callback(const WindowResizeCallback& cb);
    void set_key_press_callback(const KeyPressCallback& cb);
    void set_mose_button_pressed_callback(const MouseButtonPressedCallback& cb);
    void set_mouse_pos_changed_callaback(const MousePositionChangedCallback& cb);
    void swap_buffers();

  private:
    unsigned int m_width;
    unsigned int m_height;
    const char* m_title;

    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> m_ptr;

    WindowResizeCallback m_window_resize_callback;
    KeyPressCallback m_window_key_press_callback;
    MouseButtonPressedCallback m_mouse_button_pressed_callback;
    MousePositionChangedCallback m_mouse_position_changed_callback;
};

#endif // RT_WINDOW_H