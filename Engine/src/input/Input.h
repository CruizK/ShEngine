#pragma once

#include <glm/glm.hpp>

namespace Shengine {
	class Input
	{
	public:
		static bool IsKeyPressed(int32_t key);
		static bool IsMouseButtonPressed(int32_t button);

		static glm::vec2 GetMousePos();
		static float GetMouseX();
		static float GetMouseY();
	};
}