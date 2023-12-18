#include "tonic/core/window.h"
#include "tonic/engine.h"
#include "tonic/input/keyboard.h"
#include "tonic/graphics/helpers.h"
#include "tonic/graphics/renderapi.h"
#include <glfw/glfw3.h>

namespace tonic::core
{
WindowProperties::WindowProperties() : 
    WindowProperties("Untitled", 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, { 0.0f, 0.0f, 0.0f })
{}

WindowProperties::WindowProperties(
    const std::string &title, int w, int h, int min_w, int min_h, int max_w, int max_h, const glm::vec3 &clearcolor)
{
    this->title = title;
    this->w = w;
    this->h = h;
    this->min_w = min_w;
    this->min_h = min_h;
    this->max_w = max_w;
    this->max_h = max_h;
    this->clearcolor = clearcolor;
}

bool Window::Create(const WindowProperties& props)
{
    m_WindowProps = props;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(props.w, props.h, props.title.c_str(), nullptr, nullptr);
    if (!m_Window)
        return false;

    SetAllWindowCallbacks();
    glfwSetWindowSizeLimits(m_Window, props.min_w, props.min_h, props.max_w, props.max_h);

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    return true;
}

static auto *GetWindowInstance(GLFWwindow *win)
{
    return static_cast<Window *>(glfwGetWindowUserPointer(win));
}

void Window::SetAllWindowCallbacks()
{
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *win) {
        auto window = GetWindowInstance(win);
        if (window->m_QuitCallback)
            window->m_QuitCallback();
        else
            tonic::Engine::Instance().Quit();
    });
    glfwSetKeyCallback(m_Window, [](GLFWwindow *win, int key, int scancode, int action, int mods) {
        auto window = GetWindowInstance(win);
        if (window->m_KeyCallback)
            window->m_KeyCallback(static_cast<input::Key>(key), static_cast<input::Actions>(action), static_cast<input::Mods>(mods));
    });
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *win, double x, double y) {
        auto window = GetWindowInstance(win);
    });
    glfwSetDropCallback(m_Window, [](GLFWwindow *win, int count, const char *paths[]) {
        auto window = GetWindowInstance(win);
        if (window->m_DropCallback)
        {
            std::vector<std::string> pathsVec(paths, paths + count);
            window->m_DropCallback(pathsVec);
        }
    });
}

bool Window::HandleEvents()
{
    if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED) || 
        !glfwGetWindowAttrib(m_Window, GLFW_FOCUSED) ||
        !glfwGetWindowAttrib(m_Window, GLFW_VISIBLE))
    {
        glfwWaitEvents();
        return false;
    }
    else
    {
        glfwPollEvents();
        return true;
    }
}

void Window::Close()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);
}

void Window::BeginRender()
{
    auto &color = m_WindowProps.clearcolor;
    tonic::graphics::RenderAPI::SetClearColor(color.r, color.g, color.b, 1.0);
    tonic::graphics::RenderAPI::Clear();
}

void Window::EndRender()
{
    glfwSwapBuffers(m_Window);
}

bool Window::GetKey(input::Key key)
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::GetMouseButton(input::MouseButton mb)
{
    return glfwGetMouseButton(m_Window, mb) == GLFW_PRESS;
}

glm::vec2 Window::GetMousePosition()
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);

    return { x, y };
}
}
