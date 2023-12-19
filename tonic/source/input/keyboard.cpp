#include "tonic/input/keyboard.h"
#include "tonic/engine.h"
#include <glfw/glfw3.h>
#include <unordered_map>

namespace tonic::input
{
std::array<bool, TONIC_KEY_COUNT> Keyboard::m_Current{false};
std::array<bool, TONIC_KEY_COUNT> Keyboard::m_Last{false};

void Keyboard::Update()
{
    m_Last = m_Current;

    for (int i = 0; i < TONIC_KEY_COUNT; ++i)
    {
        m_Current[i] = Engine::Instance().GetWindow().GetKey((Key)i);
    }
}
}