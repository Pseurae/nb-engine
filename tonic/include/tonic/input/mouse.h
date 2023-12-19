#pragma once

#include <array>
#include "tonic/input/constants.h"

#include <glm/vec2.hpp>

namespace tonic
{
class Engine;
}

namespace tonic::input
{
class Mouse final
{
public:
    [[nodiscard]] static inline glm::vec2 GetPosition() { return m_CurrentPosition; }
    [[nodiscard]] static inline glm::vec2 GetRelPosition() { return m_CurrentPosition - m_LastPosition; }

    [[nodiscard]] static inline float GetX() { return m_CurrentPosition.x; }
    [[nodiscard]] static inline float GetY() { return m_CurrentPosition.y; }

    [[nodiscard]] static inline float GetRelX() { return m_CurrentPosition.x - m_LastPosition.x; }
    [[nodiscard]] static inline float GetRelY() { return m_CurrentPosition.y - m_LastPosition.y; }

    [[nodiscard]] static inline bool GetButtonUp(MouseButton button) { return !m_CurrentButtons[button] && m_LastButtons[button]; }
    [[nodiscard]] static inline bool GetButtonDown(MouseButton button) { return m_CurrentButtons[button] && !m_LastButtons[button]; }
    [[nodiscard]] static inline bool GetButtonHeld(MouseButton button) { return m_CurrentButtons[button] && m_LastButtons[button]; }

private:
    static glm::vec2 m_CurrentPosition;
    static glm::vec2 m_LastPosition;

    static std::array<bool, TONIC_MOUSEBUTTON_COUNT> m_CurrentButtons;
    static std::array<bool, TONIC_MOUSEBUTTON_COUNT> m_LastButtons;

    static void Update();

    friend class tonic::Engine;
};
}