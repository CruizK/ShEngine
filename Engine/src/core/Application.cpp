#include "Application.h"
#include "../gfx/Renderer2D.h"


namespace Shengine {

	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_ScreenWidth(1280), m_ScreenHeight(720), m_LastFrameTime(0)
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

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
	}

	void Application::Run()
	{
		while (m_Window->IsOpen())
		{
			float time = (float)glfwGetTime();
			float dt = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Window->PollEvents();

			m_Window->Clear();

			m_LayerStack.Update(dt);

			// Run draw & Update on current layer
			m_LayerStack.Draw();

			m_ImGuiHelper.Begin();
			m_LayerStack.DrawImGui();
			m_ImGuiHelper.End();

			m_Window->Display();
		}
	}

}