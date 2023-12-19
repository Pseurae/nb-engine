#pragma once

namespace tonic
{
class Engine;

namespace core
{
// TODO: Should I make this a non-static class supplied through the Engine class?
struct Time final
{
    static double deltaTime;
    static double elapsedTime;
    static double timeMult;

private:
    static double s_LastTime;

    static void Initialize();
    static void Update();

    friend class Engine;
};
}
}