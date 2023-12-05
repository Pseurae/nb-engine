#pragma once

namespace tonic::core
{
struct Time
{
    static double deltaTime;
    static double elapsedTime;
    static double timeMult;

    static double currentTime;
    static double lastTime;

    static void Initialize();
    static void Update();
};
}