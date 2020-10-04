#include "LayerStack.h"

LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
}

void LayerStack::PushLayer(Scope<Layer> layer)
{
	m_Layers.push_back(layer);
}

void LayerStack::PopLayer(Scope<Layer> layer)
{
	for (uint32_t i = 0; i < m_Layers.size(); i++)
	{
		m_Layers[i]->Destroy();
		m_Layers.erase(m_Layers.begin() + i);
		break;
	}
}

void LayerStack::Update()
{
	for (auto layer : m_Layers)
	{
		layer->Update();
	}
}

void LayerStack::Draw()
{
	for (auto layer : m_Layers)
	{
		layer->Draw();
	}
}

void LayerStack::DrawImGui()
{
	for (auto layer : m_Layers)
	{
		layer->DrawImGui();
	}
}
