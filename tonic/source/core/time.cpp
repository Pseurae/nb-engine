#include "tonic/core/time.h"
#include <glfw/glfw3.h>

namespace tonic::core
{
double Time::deltaTime;
double Time::elapsedTime;
double Time::timeMult = 1.0;

double Time::lastTime;

void Time::Initialize()
{
    lastTime = glfwGetTime();
}

void Time::Update()
{
    double currentTime = glfwGetTime();
    deltaTime = (currentTime - lastTime) * timeMult;
    elapsedTime += deltaTime;
    lastTime = currentTime;
}
}