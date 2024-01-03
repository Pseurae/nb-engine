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
    graphics::TextureFilter min_filter, mag_filter;
};

// TODO: Add event callback setters.
class Window final
{
public:
    template<typename... Args>
    using Event = void(*)(Args...);

    using QuitCallback = Event<>;
    using KeyCallback = Event<input::Key, input::Actions, input::Mods>;
    using DropCallback = Event<const std::vector<std::string> &>;
    using CursorPosCallback = Event<const glm::vec2 &>;
    using WindowResizeCallback = Event<const glm::vec2 &>;

    [[nodiscard]] bool GetKey(input::Key key) const;
    [[nodiscard]] bool GetMouseButton(input::MouseButton key) const;
    [[nodiscard]] glm::vec2 GetMousePosition() const;

    [[nodiscard]] inline GLFWwindow *GetNativeWindow() const { return m_Window; }
    [[nodiscard]] inline const WindowProperties GetWindowProps() const { return m_WindowProps; }
    [[nodiscard]] inline const auto &GetSize() const { return m_Size; }
    [[nodiscard]] inline const auto &GetFramebufferSize() const { return m_FramebufferSize; }

    inline void SetQuitCallback(const QuitCallback &f) { m_QuitCallback = f; }
    inline void SetKeyCallback(const KeyCallback &f) { m_KeyCallback = f; }
    inline void SetDropCallback(const DropCallback &f) { m_DropCallback = f; }
    inline void SetCursorPosCallback(const CursorPosCallback &f) { m_CursorPosCallback = f; }
    inline void SetWindowResizeCallback(const WindowResizeCallback &f) { m_WindowResizeCallback = f; }

private:
    bool Create(const WindowProperties &props);
    void Close();
    bool HandleEvents();

    void InitializeScreenRender();
    void RenderToScreen();

    void BeginRender();
    void EndRender();

    void SetAllWindowCallbacks();

    QuitCallback m_QuitCallback = nullptr;
    KeyCallback m_KeyCallback = nullptr;
    DropCallback m_DropCallback = nullptr;
    CursorPosCallback m_CursorPosCallback = nullptr;
    WindowResizeCallback m_WindowResizeCallback = nullptr;

    WindowProperties m_WindowProps;
    GLFWwindow *m_Window;

    glm::ivec2 m_Size, m_FramebufferSize;
    friend class tonic::Engine;
};
}