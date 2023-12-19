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
struct WindowProperties final
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

// TODO: Add event callback setters.
class Window final
{
public:
    [[nodiscard]] bool GetKey(input::Key key) const;
    [[nodiscard]] bool GetMouseButton(input::MouseButton key) const;
    [[nodiscard]] glm::vec2 GetMousePosition() const;

    [[nodiscard]] inline GLFWwindow *GetNativeWindow() const { return m_Window; }
    [[nodiscard]] inline const WindowProperties GetWindowProps() const { return m_WindowProps; }
    [[nodiscard]] inline const auto &GetSize() const { return m_Size; }
    [[nodiscard]] inline const auto &GetFramebufferSize() const { return m_FramebufferSize; }

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