#pragma once

#include <array>
#include "tonic/input/constants.h"

#include <glm/vec2.hpp>

namespace tonic::input
{
class Mouse
{
public:
    static void Update();

    static inline glm::vec2 GetPosition() { return m_CurrentPosition; }
    static inline glm::vec2 GetRelPosition() { return m_CurrentPosition - m_LastPosition; }

    static inline float GetX() { return m_CurrentPosition.x; }
    static inline float GetY() { return m_CurrentPosition.y; }

    static inline float GetRelX() { return m_CurrentPosition.x - m_LastPosition.x; }
    static inline float GetRelY() { return m_CurrentPosition.y - m_LastPosition.y; }

    static inline bool GetButtonUp(MouseButton button) { return !m_CurrentButtons[button] && m_LastButtons[button]; }
    static bool GetButtonDown(MouseButton button) { return m_CurrentButtons[button] && !m_LastButtons[button]; }
    static bool GetButtonHeld(MouseButton button) { return m_CurrentButtons[button] && m_LastButtons[button]; }

private:
    static glm::vec2 m_CurrentPosition;
    static glm::vec2 m_LastPosition;

    static std::array<bool, TONIC_MOUSEBUTTON_COUNT> m_CurrentButtons;
    static std::array<bool, TONIC_MOUSEBUTTON_COUNT> m_LastButtons;
};
}