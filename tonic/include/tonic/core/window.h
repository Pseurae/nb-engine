#pragma once

#include <string>
#include <glm/vec3.hpp>

struct GLFWwindow;

namespace tonic::core
{
struct WindowProperties
{
    WindowProperties();
    WindowProperties(const std::string &title,int w, int h, int mnw, int mnh, int mxw, int mxh, const glm::vec3 &clearcolor);

    std::string title;
    int w, h;
    int min_w, min_h;
    int max_w, max_h;
    glm::vec3 clearcolor;
};

class Window
{
public:
    bool Create(const WindowProperties &props);
    void Close();
    bool HandleEvents();

    void BeginRender();
    void EndRender();

    GLFWwindow *GetGLFWWindow() const { return m_Window; }

private:
    WindowProperties m_WindowProps;
    GLFWwindow *m_Window;
};
}