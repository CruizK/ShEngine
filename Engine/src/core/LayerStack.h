#pragma once

#include "Layer.h"
#include <vector>

namespace Shengine {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void Update(float dt);
		void Draw();
		void DrawImGui();

	private:
		std::vector<Layer*> m_Layers;
	};

}