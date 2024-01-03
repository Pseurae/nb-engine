#include "tonic/engine.h"
#include "tonic/core/time.h"
#include "tonic/input/keyboard.h"
#include "tonic/input/mouse.h"
#include "tonic/graphics/renderapi.h"
#include "tonic/log.h"

#include <GL/gl3w.h>
#include <glfw/glfw3.h>

namespace tonic
{
Engine *Engine::s_Instance = nullptr;

Engine& Engine::Instance()
{
    if (!s_Instance) s_Instance = new Engine();
    return *s_Instance;
}

bool Engine::Run(App *app)
{
    TONIC_ASSERT(m_App == nullptr, "An instance of 'App' is already running.");
    m_App = app;

    if (Initialize())
    {
        while (m_IsRunning)
        {
            if (m_Window.HandleEvents())
            {
                Update();
                Render();
            }
        }

        Shutdown();
        return true;
    }
    else
    {
        Shutdown();
        return false;
    }
}

void error_callback(int code, const char* description)
{
    TONIC_ERROR("GLFW Error [%i]: %s", code, description);
}

bool Engine::Initialize()
{
    m_IsRunning = true;

    glfwSetErrorCallback(error_callback);

    if (glfwInit() == GLFW_FALSE)
        return false;

    if (!m_Window.Create(m_App->GetWindowProperties()))
        return false;

    if (gl3wInit() != GL3W_OK)
        return false;

    m_Window.InitializeScreenRender();

    core::Time::Initialize();
    graphics::RenderAPI::Initialize();

    m_App->OnInitialize();

    return true;
}

void Engine::Shutdown()
{
    m_Window.Close();
    m_App->OnShutdown();
    glfwTerminate();
}

void Engine::Quit(void)
{
    Instance().m_IsRunning = false;
}

void Engine::Update()
{
    input::Keyboard::Update();
    input::Mouse::Update();
    core::Time::Update();
    m_App->OnUpdate();
}

void Engine::Render()
{
    m_Window.BeginRender();
    m_App->OnRender();
    m_Window.EndRender();
}

Engine::Engine() :
    m_App(nullptr), m_IsRunning(false)
{}
}