#pragma once

#include "../core/Layer.h"

namespace Shengine {

	class ImGuiHelper
	{
	public:
		ImGuiHelper();
		~ImGuiHelper();
	
		void Init();


		void Begin();
		void End();
	};
}