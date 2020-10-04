#include "ImGuiHelper.h"
#include "../core/Application.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


namespace Shengine {
	ImGuiHelper::ImGuiHelper()
	{
	}

	ImGuiHelper::~ImGuiHelper()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiHelper::Init()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(
			Application::Get().GetWindow()->GetWindowPtr(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}

	void ImGuiHelper::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiHelper::End()
	{
		ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}