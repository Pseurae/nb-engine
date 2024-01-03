#include "tonic/input/mouse.h"
#include "tonic/engine.h"
#include <glfw/glfw3.h>

namespace tonic::input
{
std::array<bool, TONIC_MOUSEBUTTON_COUNT> Mouse::m_CurrentButtons;
std::array<bool, TONIC_MOUSEBUTTON_COUNT> Mouse::m_LastButtons;
glm::vec2 Mouse::m_CurrentPosition;
glm::vec2 Mouse::m_LastPosition;

void Mouse::Update()
{
    m_LastButtons = m_CurrentButtons;
    auto &window = Engine::GetWindow();

    for (int i = 0; i < TONIC_MOUSEBUTTON_COUNT; ++i)
    {
        m_CurrentButtons[i] = window.GetMouseButton(static_cast<input::MouseButton>(i));        
    }

    m_LastPosition = m_CurrentPosition;
    m_CurrentPosition = window.GetMousePosition();
}
}