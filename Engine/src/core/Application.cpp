#include "Application.h"
#include "../gfx/Renderer2D.h"

Application* Application::s_Instance = nullptr;

Application::Application():
	m_ScreenWidth(1280), m_ScreenHeight(720)
{
	Log::Init();
	s_Instance = this;
	m_Window = CreateScope<Window>();
	m_Window->Create("Window", m_ScreenWidth, m_ScreenHeight);
	Renderer2D::Init();
	m_ImGuiHelper.Init();
	
}

Application::~Application()
{
	
}

void Application::Run()
{
	while (m_Window->IsOpen())
	{
		m_Window->PollEvents();

		m_Window->Clear();

		m_LayerStack.Update();

		// Run draw & Update on current scene
		m_LayerStack.Draw();

		m_ImGuiHelper.Begin();
		m_LayerStack.DrawImGui();
		m_ImGuiHelper.End();

		m_Window->Display();
	}
}
