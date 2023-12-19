#include "tonic/core/time.h"
#include <glfw/glfw3.h>

namespace tonic::core
{
double Time::deltaTime;
double Time::elapsedTime;
double Time::timeMult = 1.0;

double Time::s_LastTime;

void Time::Initialize()
{
    s_LastTime = glfwGetTime();
}

void Time::Update()
{
    double currentTime = glfwGetTime();
    deltaTime = (currentTime - s_LastTime) * timeMult;
    elapsedTime += deltaTime;
    s_LastTime = currentTime;
}
}