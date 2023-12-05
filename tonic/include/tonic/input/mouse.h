#pragma once

#include <array>

namespace tonic::input
{
enum MouseButton
{
    TONIC_MOUSEBUTTON_LEFT,
    TONIC_MOUSEBUTTON_RIGHT,
    TONIC_MOUSEBUTTON_MIDDLE,
    TONIC_MOUSEBUTTON_COUNT
};

class Mouse
{
public:
    static void Update();
    static bool GetButtonUp(MouseButton button);
    static bool GetButtonDown(MouseButton button);
    static bool GetButtonHeld(MouseButton button);
private:
    static std::array<bool, TONIC_MOUSEBUTTON_COUNT> m_Current;
    static std::array<bool, TONIC_MOUSEBUTTON_COUNT> m_Last;
};
}