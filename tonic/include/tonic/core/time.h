#pragma once

namespace tonic
{
class Engine;

namespace core
{
struct Time
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