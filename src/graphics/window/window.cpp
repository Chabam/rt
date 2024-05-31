#include <rt/graphics/window/window.hpp>
#include <rt/utils/logger.hpp>

#include <GLFW/glfw3.h>
#include <math.h>

struct Window::Impl
{
    static void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (window == nullptr)
        {
            Logger::error("Provided pointer to window is NULL!");
            return;
        }

        window->m_window_key_press_callback(key, action);
    }

    static void resizeCallback(GLFWwindow* glfwWindow, int width, int height)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (window == nullptr)
        {
            Logger::error("Provided pointer to window is NULL!");
            return;
        }

        window->m_window_resize_callback(width, height);
        window->m_width = width;
        window->m_height = height;
    }

    static void mouseButtonPressedCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (window == nullptr)
        {
            Logger::error("Provided pointer to window is NULL!");
            return;
        }

        window->m_mouse_button_pressed_callback(button, action, mods);
    }

    static void mousePositionChangedCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (window == nullptr)
        {
            Logger::error("Provided pointer to window is NULL!");
            return;
        }

        window->m_mouse_position_changed_callback(xpos, ypos);
    }

    GLFWwindow* m_windowPtr;

    Impl(Window& window, unsigned int width, unsigned int height, const char* title)
        : m_windowPtr(glfwCreateWindow(width, height, title, nullptr, nullptr))
    {
        if (!m_windowPtr)
        {
            throw std::runtime_error("Could not create a GLWF window!");
        }
        glfwSetWindowAspectRatio(m_windowPtr, 16, 9);

        // Events
        glfwSetWindowUserPointer(m_windowPtr, &window);
        glfwSetKeyCallback(m_windowPtr, Window::Impl::keyCallback);
        glfwSetWindowSizeCallback(m_windowPtr, Window::Impl::resizeCallback);
        glfwSetCursorPosCallback(m_windowPtr, Window::Impl::mousePositionChangedCallback);
        glfwSetMouseButtonCallback(m_windowPtr, Window::Impl::mouseButtonPressedCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        glfwMakeContextCurrent(m_windowPtr);
    }

    ~Impl() { glfwDestroyWindow(m_windowPtr); }
};

Window::Window()
    : m_width()
    , m_height()
    , m_title("New window")
    , m_window_resize_callback([](int, int) {})
    , m_window_key_press_callback([](int, int) {})
    , m_mouse_button_pressed_callback([](int, int, int) {})
    , m_mouse_position_changed_callback([](double, double) {})
{
}

Window::Window(unsigned int width, unsigned int height, const char* title)
    : m_width(width)
    , m_height(height)
    , m_title(title)
    , m_impl(std::make_unique<Window::Impl>(*this, width, height, title))
    , m_window_resize_callback([](int, int) {})
    , m_window_key_press_callback([](int, int) {})
    , m_mouse_button_pressed_callback([](int, int, int) {})
    , m_mouse_position_changed_callback([](double, double) {})
{
}

Window::~Window()
{
}

void Window::set_size(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Window::close()
{
    Logger::info("Closing window");
    glfwSetWindowShouldClose(m_impl->m_windowPtr, GLFW_TRUE);
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_impl->m_windowPtr);
}

void Window::swap_buffers()
{
    glfwSwapBuffers(m_impl->m_windowPtr);
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