#include "LayerStack.h"

namespace Shengine {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		m_Layers.back()->Init();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		for (uint32_t i = 0; i < m_Layers.size(); i++)
		{
			m_Layers[i]->Destroy();
			delete m_Layers[i];
			m_Layers.erase(m_Layers.begin() + i);
			break;
		}
	}

	void LayerStack::Update(float dt)
	{
		for (auto layer : m_Layers)
		{
			layer->Update(dt);
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
}