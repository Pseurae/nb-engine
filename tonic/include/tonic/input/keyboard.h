#pragma once

#include <array>
#include "tonic/input/constants.h"

namespace tonic
{
class Engine;
}

namespace tonic::input
{
class Keyboard final
{
public:
    [[nodiscard]] static inline bool GetKeyDown(Key key) { return m_Current[key] && !m_Last[key]; }
    [[nodiscard]] static inline bool GetKeyUp(Key key) { return !m_Current[key] && m_Last[key]; }
    [[nodiscard]] static inline bool GetKeyHeld(Key key) { return m_Current[key] && m_Last[key]; }

private:
    static std::array<bool, TONIC_KEY_COUNT> m_Current;
    static std::array<bool, TONIC_KEY_COUNT> m_Last;

    static void Update();

    friend class Engine;
};
}