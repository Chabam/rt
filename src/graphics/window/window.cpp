#include <rt/graphics/window/window.hpp>
#include <rt/utils/logger.hpp>

#include <GLFW/glfw3.h>

Window::Window(unsigned int width, unsigned int height, const char* title)
    : m_logger{std::vformat("window|{}", std::make_format_args(title)).c_str()}
    , m_width{width}
    , m_height{height}
    , m_title{title}
    , m_ptr{glfwCreateWindow(width, height, title, nullptr, nullptr)}
    , m_window_resize_callback{[](int, int) {}}
    , m_window_key_press_callback{[](int, int) {}}
    , m_mouse_button_pressed_callback{[](int, int, int) {}}
    , m_mouse_position_changed_callback{[](double, double) {}}
{
    if (!m_ptr)
    {
        throw std::runtime_error("Could not create a GLWF window!");
    }
    glfwSetWindowAspectRatio(m_ptr, 16, 9);

    using namespace std::placeholders;

    glfwSetWindowUserPointer(m_ptr, this);

    glfwSetKeyCallback(m_ptr, [](GLFWwindow* glfwWindow, int key, [[maybe_unused]] int scancode, int action,
                                 [[maybe_unused]] int mods) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->m_window_key_press_callback(key, action);
    });

    glfwSetWindowSizeCallback(m_ptr, [](GLFWwindow* glfwWindow, int width, int height) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->m_window_resize_callback(width, height);
        window->m_width = width;
        window->m_height = height;
    });

    glfwSetCursorPosCallback(m_ptr, [](GLFWwindow* glfwWindow, double xpos, double ypos) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->m_mouse_position_changed_callback(xpos, ypos);
    });

    glfwSetMouseButtonCallback(m_ptr, [](GLFWwindow* glfwWindow, int button, int action, int mods) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->m_mouse_button_pressed_callback(button, action, mods);
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    glfwMakeContextCurrent(m_ptr);
    glfwSwapInterval(0);
}

Window::~Window()
{
    glfwDestroyWindow(m_ptr);
}

// Window::Window(Window&& other)
//     : m_logger{std::move(other.m_logger)}
//     , m_width{std::move(other.m_width)}
//     , m_height{std::move(other.m_height)}
//     , m_title{std::move(other.m_title)}
//     , m_window_resize_callback{std::move(other.m_window_resize_callback)}
//     , m_window_key_press_callback{std::move(other.m_window_key_press_callback)}
//     , m_mouse_button_pressed_callback{std::move(other.m_mouse_button_pressed_callback)}
//     , m_mouse_position_changed_callback{std::move(other.m_mouse_position_changed_callback)}
// {
// }

// Window& Window::operator=(Window&& other)
// {
//     m_logger = std::move(other.m_logger);
//     m_width = std::move(other.m_width);
//     m_height = std::move(other.m_height);
//     m_title = std::move(other.m_title);
//     m_window_resize_callback = std::move(other.m_window_resize_callback);
//     m_window_key_press_callback = std::move(other.m_window_key_press_callback);
//     m_mouse_button_pressed_callback = std::move(other.m_mouse_button_pressed_callback);
//     m_mouse_position_changed_callback = std::move(other.m_mouse_position_changed_callback);

//     return *this;
// }

void Window::set_title(const char* title)
{
    m_title = title;
    glfwSetWindowTitle(m_ptr, title);
}

void Window::set_size(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Window::close()
{
    m_logger.info("Closing window");
    glfwSetWindowShouldClose(m_ptr, GLFW_TRUE);
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_ptr);
}

void Window::swap_buffers()
{
    glfwSwapBuffers(m_ptr);
}

unsigned int Window::get_width() const
{
    return m_width;
}

unsigned int Window::get_height() const
{
    return m_height;
}

void Window::set_resize_callback(const WindowResizeCallback& cb)
{
    m_window_resize_callback = cb;
}

void Window::set_key_press_callback(const KeyPressCallback& cb)
{
    m_window_key_press_callback = cb;
}

void Window::set_mouse_pos_changed_callaback(const MousePositionChangedCallback& cb)
{
    m_mouse_position_changed_callback = cb;
}

void Window::set_mose_button_pressed_callback(const MouseButtonPressedCallback& cb)
{
    m_mouse_button_pressed_callback = cb;
}