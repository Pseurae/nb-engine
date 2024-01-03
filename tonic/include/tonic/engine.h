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

class Engine final
{
public:
    static Engine &Instance();
    [[nodiscard]] static core::Window &GetWindow() { return Instance().m_Window; }
    static void Quit();

    Engine(const Engine &) = delete;
    void operator=(const Engine &) = delete;

    Engine(Engine &&) = delete;
    void operator=(Engine &&) = delete;

    bool Run(App *app);

private:
    bool Initialize();
    void Shutdown();

    void Update();
    void Render();

    App *m_App;
    bool m_IsRunning;
    core::Window m_Window;

    Engine();
    static Engine *s_Instance;
};
}