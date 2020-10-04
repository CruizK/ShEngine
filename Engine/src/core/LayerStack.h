#pragma once

#include "Layer.h"
#include <vector>

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Scope<Layer> layer);
	void PopLayer(Scope<Layer> layer);

	void Update();
	void Draw();
	void DrawImGui();

private:
	std::vector<Scope<Layer>> m_Layers;
};