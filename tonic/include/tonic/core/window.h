#pragma once

#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "tonic/input/constants.h"

struct GLFWwindow;

namespace tonic::core
{
struct WindowProperties
{
    WindowProperties();
    WindowProperties(const std::string &title,int w, int h, int mnw, int mnh, int mxw, int mxh, const glm::vec3 &clearcolor);

    std::string title;
    int w, h;
    int min_w, min_h;
    int max_w, max_h;
    glm::vec3 clearcolor;
};

template<typename... Args>
using Event = void(*)(Args...);

class Window
{
public:
    bool Create(const WindowProperties &props);
    void Close();
    bool HandleEvents();

    void BeginRender();
    void EndRender();

    bool GetKey(input::Key key);
    bool GetMouseButton(input::MouseButton key);
    glm::vec2 GetMousePosition();

    GLFWwindow *GetNativeWindow() const { return m_Window; }

private:
    void SetAllWindowCallbacks();

    Event<> m_QuitCallback = nullptr;
    Event<input::Key, input::Actions, input::Mods> m_KeyCallback = nullptr;
    Event<const std::vector<std::string> &> m_DropCallback = nullptr;
    Event<const glm::vec2 &> m_CursorPosCallback;  

    WindowProperties m_WindowProps;
    GLFWwindow *m_Window;
};
}