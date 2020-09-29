#include "Window.h"
#include "../gfx/GLCall.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

Window::Window() 
    : m_Window(nullptr), m_UsingImGui(false)
{

}

Window::Window(const std::string& title, uint32_t width, uint32_t height)
    : m_Window(nullptr), m_UsingImGui(false)
{
    Create(title, width, height);
}

Window::~Window()
{
    if(m_UsingImGui)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::Create(const std::string& title, uint32_t width, uint32_t height)
{
    Log::Init();
    m_Data.Title = title;
    m_Data.Width = width;
    m_Data.Height = height;
    m_Data.IsOpen = true;

    if(!glfwInit())
    {
        CORE_ERROR("GLFW INIT FAILED");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);

    if(m_Window == nullptr)
    {
        CORE_ERROR("WINDOW FAILED TO BE CREATED");
        return;
    }

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        CORE_ERROR("GLAD INIT FAILED");
        return;
    }

    glfwSwapInterval(0);

    GLCall(glViewport(0, 0, m_Data.Width, m_Data.Height));

    //GLCall(glEnable(GL_BLEND));
    //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.IsOpen = false;
    });

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;
        GLCall(glViewport(0, 0, data.Width, data.Height));
    });
}

void Window::UseImGui()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    m_UsingImGui = true;
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::Clear()
{
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    if (m_UsingImGui)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
}

void Window::Display()
{
    if (m_UsingImGui)
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    glfwSwapBuffers(m_Window);
}