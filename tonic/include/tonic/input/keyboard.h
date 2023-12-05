#pragma once

#include <array>

namespace tonic::input
{
enum Key : short
{
    TONIC_KEY_ENTER,
    TONIC_KEY_COUNT
};

class Keyboard
{
public:
    static void Update();
    static bool GetKeyDown(Key key);
    static bool GetKeyUp(Key key);
    static bool GetKeyHeld(Key key);

private:
    static int GetGLFWKey(Key key);
    static std::array<bool, TONIC_KEY_COUNT> m_Current;
    static std::array<bool, TONIC_KEY_COUNT> m_Last;
};
}