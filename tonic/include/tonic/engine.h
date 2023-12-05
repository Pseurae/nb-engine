#pragma once

#include "tonic/core/window.h"

namespace tonic
{
class App
{
public:
    App() { };
    ~App() { };

    virtual const core::WindowProperties GetWindowProperties() { return core::WindowProperties(); }
    virtual void OnInitialize() { }
    virtual void OnShutdown() { }
    virtual void OnRender() { }
    virtual void OnUpdate() { }
};

class Engine
{
public:
    static Engine &Instance();

    bool Run(App *app);
    bool Initialize();
    void Shutdown();
    void Quit();

    void Update();
    void Render();
    GLFWwindow *GetNativeWindow() const;
private:
    App *m_App;
    bool m_IsRunning;
    core::Window m_Window;

    Engine();
    static Engine *s_Instance;
};
}