#pragma once
#include "Base.h"
#include "Window.h"
#include "LayerStack.h"
#include "../imgui/ImGuiHelper.h"


int main(int argc, char** argv);

namespace Shengine {

	class Application
	{
	public:
		Application();
		~Application();

		const Scope<Window>& GetWindow() { return m_Window; }

		static Application& Get() { return *s_Instance; }

	private:
		void Run();

		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiHelper m_ImGuiHelper;
		uint32_t m_ScreenWidth, m_ScreenHeight;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
}