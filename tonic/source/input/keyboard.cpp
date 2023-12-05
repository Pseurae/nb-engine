#include "tonic/input/keyboard.h"
#include "tonic/engine.h"
#include <glfw/glfw3.h>
#include <unordered_map>

namespace tonic::input
{
std::array<bool, TONIC_KEY_COUNT> Keyboard::m_Current{false};
std::array<bool, TONIC_KEY_COUNT> Keyboard::m_Last{false};

static const std::unordered_map<Key, int> _keyToGLFW = 
{
    { TONIC_KEY_ENTER, GLFW_KEY_ENTER }
};

int Keyboard::GetGLFWKey(Key key)
{
    if (_keyToGLFW.count(key) > 0)
        return _keyToGLFW.at(key);
    return -1;
}

void Keyboard::Update()
{
    m_Last = m_Current;
    GLFWwindow *win = Engine::Instance().GetNativeWindow();

    for (int i = 0; i < TONIC_KEY_COUNT; ++i)
    {
        int key = GetGLFWKey((Key)i);
        if (key == -1)
            continue;

        int state = glfwGetKey(win, key);

        m_Current[i] = state == GLFW_PRESS;
    }
}

bool Keyboard::GetKeyUp(Key key)
{
    return !m_Current[key] && m_Last[key];
}

bool Keyboard::GetKeyDown(Key key)
{
    return m_Current[key] && !m_Last[key];
}

bool Keyboard::GetKeyHeld(Key key)
{
    return m_Current[key] && m_Last[key];
}
}