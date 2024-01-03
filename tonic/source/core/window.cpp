#include "tonic/core/window.h"
#include "tonic/engine.h"
#include "tonic/input/keyboard.h"
#include "tonic/graphics/framebuffer.h"
#include "tonic/graphics/vertex.h"
#include "tonic/graphics/shader.h"
#include "tonic/graphics/helpers.h"
#include "tonic/graphics/renderapi.h"
#include <glfw/glfw3.h>
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tonic::core
{
WindowProperties::WindowProperties()
{
    title = "Untitled";
    size = { 800, 600 };
    min_size = { GLFW_DONT_CARE, GLFW_DONT_CARE };
    min_size = { GLFW_DONT_CARE, GLFW_DONT_CARE };
    clearcolor = { 0.0f, 0.0f, 0.0f };
    min_filter = tonic::graphics::TextureFilter::Linear;
    mag_filter = tonic::graphics::TextureFilter::Linear;
}

struct WindowRenderStorage final
{
    std::shared_ptr<graphics::FrameBuffer> FBO;
    std::shared_ptr<graphics::VertexArray> VAO;
    std::shared_ptr<graphics::VertexBuffer> VBO;
    std::shared_ptr<graphics::ElementBuffer> EBO;
    std::shared_ptr<graphics::VertexBufferLayout> VBOLayout;
    std::shared_ptr<graphics::Shader> Shader;
};

static WindowRenderStorage *sRenderData;

bool Window::Create(const WindowProperties& props)
{
    m_WindowProps = props;
    sRenderData = new WindowRenderStorage();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(props.size.x, props.size.y, props.title.c_str(), nullptr, nullptr);
    if (!m_Window)
        return false;
    
    glfwSetWindowAspectRatio(m_Window, props.size.x, props.size.y);

    SetAllWindowCallbacks();
    glfwGetFramebufferSize(m_Window, &m_FramebufferSize.x, &m_FramebufferSize.y);
    glfwSetWindowSizeLimits(m_Window, props.min_size.x, props.min_size.y, props.max_size.x, props.max_size.y);

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    return true;
}

void Window::InitializeScreenRender()
{
    const float vertices[] = {
        -1.0f, -1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 0.0f
    };

    const unsigned int elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    const char *vertexShaderSource = R"glsl(
    #version 330 core

    layout (location = 0) in vec2 position;
    layout (location = 1) in vec2 uv;

    out vec2 fragCoords;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
        fragCoords = uv;
    }
    )glsl";

    const char *fragmentShaderSource = R"glsl(
    #version 330 core

    out vec4 fragColor;

    in vec2 fragCoords;

    uniform sampler2D texture0;

    void main()
    {
        fragColor = texture2D(texture0, fragCoords);
    }
    )glsl";

    sRenderData->VBO = std::make_shared<tonic::graphics::VertexBuffer>((void *)vertices, (unsigned int)sizeof(vertices));
    sRenderData->VBOLayout = std::make_shared<tonic::graphics::VertexBufferLayout>();
    sRenderData->VBOLayout->Push<float>(2);
    sRenderData->VBOLayout->Push<float>(2);

    sRenderData->EBO = std::make_shared<tonic::graphics::ElementBuffer>(elements, 6);

    sRenderData->VAO = std::make_shared<tonic::graphics::VertexArray>();
    sRenderData->VAO->SubmitBuffer(*sRenderData->VBO, *sRenderData->VBOLayout);

    sRenderData->Shader = std::make_shared<tonic::graphics::Shader>(vertexShaderSource, fragmentShaderSource);
    sRenderData->FBO = std::make_shared<tonic::graphics::FrameBuffer>(m_WindowProps.size.x, m_WindowProps.size.y);
    sRenderData->FBO->GetTexture().SetFilter(m_WindowProps.min_filter, m_WindowProps.mag_filter);
}

void Window::RenderToScreen()
{
    sRenderData->Shader->Use();
    sRenderData->VAO->Bind();
    sRenderData->EBO->Bind();

    tonic::graphics::RenderAPI::ActivateTexture(0);
    sRenderData->FBO->GetTexture().Bind();

    sRenderData->Shader->SetUniform("texture0", 0);

    tonic::graphics::RenderAPI::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
            tonic::Engine::Quit();
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

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *win, int w, int h) {
        auto window = GetWindowInstance(win);

        window->m_Size = { w, h };

        if (window->m_WindowResizeCallback)
            window->m_WindowResizeCallback(glm::vec2(w, h));
    });

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *win, int w, int h) {
        auto window = GetWindowInstance(win);
        window->m_FramebufferSize = { w, h };
        glViewport(0, 0, w, h);
        graphics::RenderAPI::Clear();
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
    delete sRenderData;
    if (m_Window)
        glfwDestroyWindow(m_Window);
}

void Window::BeginRender()
{
    auto &color = m_WindowProps.clearcolor;

    tonic::graphics::RenderAPI::SetClearColor(color.r, color.g, color.b, 1.0);
    tonic::graphics::RenderAPI::Clear();
    tonic::graphics::RenderAPI::PushFramebuffer(sRenderData->FBO);
}

void Window::EndRender()
{
    tonic::graphics::RenderAPI::PopFramebuffer();

    RenderToScreen();
    glfwSwapBuffers(m_Window);
}

bool Window::GetKey(input::Key key) const
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::GetMouseButton(input::MouseButton mb) const
{
    return glfwGetMouseButton(m_Window, mb) == GLFW_PRESS;
}

glm::vec2 Window::GetMousePosition() const
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);

    return { x, y };
}
}
