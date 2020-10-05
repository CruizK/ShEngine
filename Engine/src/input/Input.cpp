#include "Input.h"
#include "../core/Application.h"


namespace Shengine {

	bool Input::IsKeyPressed(int32_t key)
	{
		return glfwGetKey(Application::Get().GetWindow()->GetWindowPtr(), key);
	}

	bool Input::IsMouseButtonPressed(int32_t button)
	{
		return glfwGetMouseButton(Application::Get().GetWindow()->GetWindowPtr(), button);
	}

	glm::vec2 Input::GetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(Application::Get().GetWindow()->GetWindowPtr(), &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePos().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePos().y;
	}
}