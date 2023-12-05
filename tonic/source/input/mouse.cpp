#include "tonic/input/mouse.h"
#include "tonic/engine.h"
#include <glfw/glfw3.h>

namespace tonic::input
{
std::array<bool, TONIC_MOUSEBUTTON_COUNT> Mouse::m_Current;
std::array<bool, TONIC_MOUSEBUTTON_COUNT> Mouse::m_Last;

void Mouse::Update()
{
    m_Last = m_Current;

    for (int i = 0; i < TONIC_MOUSEBUTTON_COUNT; ++i)
    {
        m_Current[i] = glfwGetMouseButton(Engine::Instance().GetNativeWindow(), i) == GLFW_PRESS;        
    }
}

bool Mouse::GetButtonUp(MouseButton button)
{
    return !m_Current[button] && m_Last[button];
}

bool Mouse::GetButtonDown(MouseButton button)
{
    return m_Current[button] && !m_Last[button];
}

bool Mouse::GetButtonHeld(MouseButton button)
{
    return m_Current[button] && m_Last[button];
}
}