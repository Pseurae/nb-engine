#include "tonic/core/window.h"
#include "tonic/engine.h"
#include "tonic/input/keyboard.h"
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

    glfwSetWindowSizeLimits(m_Window, props.min_w, props.min_h, props.max_w, props.max_h);
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *) { 
        tonic::Engine::Instance().Quit(); 
    });
    glfwSetKeyCallback(m_Window, [](GLFWwindow *, int key, int scancode, int action, int mods) { 
        printf("%i\n", action);
    });

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    return true;
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
    glClearColor(color.r, color.g, color.b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndRender()
{
    glfwSwapBuffers(m_Window);
}
}
