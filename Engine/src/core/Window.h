#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window();
    Window(const std::string &title, uint32_t width, uint32_t height);
    ~Window();

    void Create(const std::string &title, uint32_t width, uint32_t height);

    inline bool IsOpen() { return m_Data.IsOpen; }


    void PollEvents();
    void Clear();
    void Display();

    inline GLFWwindow* GetWindowPtr() { return m_Window; }

private:
    GLFWwindow *m_Window;

    struct WindowData
    {
        std::string Title;
        uint32_t Width, Height;
        bool IsOpen;
    };

    WindowData m_Data;
};