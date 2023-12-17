#pragma once

#include <array>
#include "tonic/input/constants.h"

namespace tonic::input
{
class Keyboard
{
public:
    static void Update();
    static bool GetKeyDown(Key key) { return m_Current[key] && !m_Last[key]; }
    static bool GetKeyUp(Key key) { return !m_Current[key] && m_Last[key]; }
    static bool GetKeyHeld(Key key) { return m_Current[key] && m_Last[key]; }

private:
    static std::array<bool, TONIC_KEY_COUNT> m_Current;
    static std::array<bool, TONIC_KEY_COUNT> m_Last;
};
}