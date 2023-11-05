#include "window.h"

#include <GLFW/glfw3.h>
#include <utils/logger.h>
#include <math.h>

struct Window::Impl
{
    static void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
    {
        Logger::debug("Creating window");
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (window == nullptr)
        {
            Logger::error("Provided pointer to window is NULL!");
            return;
        }

        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            window->m_windowKeyPressCallback(key);
        }
    }

    static void resizeCallback(GLFWwindow* glfwWindow, int width, int height)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (window == nullptr)
        {
            Logger::error("Provided pointer to window is NULL!");
            return;
        }

        window->m_windowResizeCallback(width, height);
        window->m_width = width;
        window->m_height = height;
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
        glfwMakeContextCurrent(m_windowPtr);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    }

    ~Impl()
    {
        glfwDestroyWindow(m_windowPtr);
    }
};

Window::Window()
    : m_width()
    , m_height()
    , m_title("New window")
    , m_windowResizeCallback([](int, int) {})
    , m_windowKeyPressCallback([](int) {})
{
}

Window::Window(unsigned int width, unsigned int height, const char* title)
    : m_width(width)
    , m_height(height)
    , m_title(title)
    , m_impl(std::make_unique<Window::Impl>(*this, width, height, title))
    , m_windowResizeCallback([](int, int) {})
    , m_windowKeyPressCallback([](int) {})
{
}

Window::~Window()
{
}

void Window::setSize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Window::setToClose()
{
    Logger::info("Closing window");
    glfwSetWindowShouldClose(m_impl->m_windowPtr, GLFW_TRUE);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_impl->m_windowPtr);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_impl->m_windowPtr);
}

unsigned int Window::getWidth() const
{
    return m_width;
}

unsigned int Window::getHeight() const
{
    return m_height;
}

void Window::setResizeCallback(WindowResizeCallback cb)
{
    m_windowResizeCallback = cb;
}

void Window::setKeyPressCallback(KeyPressCallback cb)
{
    m_windowKeyPressCallback = cb;
}