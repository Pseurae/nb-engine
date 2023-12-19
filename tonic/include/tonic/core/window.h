#pragma once

#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "tonic/input/constants.h"
#include "tonic/graphics/texture.h"

struct GLFWwindow;

namespace tonic
{
class Engine;
}

namespace tonic::core
{
struct WindowProperties
{
    WindowProperties();

    std::string title;
    glm::ivec2 size;
    glm::ivec2 min_size;
    glm::ivec2 max_size;
    glm::vec3 clearcolor;
    tonic::graphics::TextureFilter min_filter, mag_filter;
};

template<typename... Args>
using Event = void(*)(Args...);

class Window
{
public:
    bool GetKey(input::Key key);
    bool GetMouseButton(input::MouseButton key);
    glm::vec2 GetMousePosition();

    GLFWwindow *GetNativeWindow() const { return m_Window; }
    const WindowProperties GetWindowProps() const { return m_WindowProps; }
    const auto &GetSize() const { return m_Size; }
    const auto &GetFramebufferSize() const { return m_FramebufferSize; }

    friend class tonic::Engine;

private:
    bool Create(const WindowProperties &props);
    void Close();
    bool HandleEvents();

    void InitializeScreenRender();
    void RenderToScreen();

    void BeginRender();
    void EndRender();

    void SetAllWindowCallbacks();

    Event<> m_QuitCallback = nullptr;
    Event<input::Key, input::Actions, input::Mods> m_KeyCallback = nullptr;
    Event<const std::vector<std::string> &> m_DropCallback = nullptr;
    Event<const glm::vec2 &> m_CursorPosCallback = nullptr;
    Event<const glm::vec2 &> m_WindowResizeCallback = nullptr;

    WindowProperties m_WindowProps;
    GLFWwindow *m_Window;

    glm::ivec2 m_Size, m_FramebufferSize;
};
}