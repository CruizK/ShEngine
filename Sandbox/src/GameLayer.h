#pragma once

#include <core/Layer.h>
#include <gfx/Renderable2D.h>
#include <gfx/Renderer2D.h>

class GameLayer : public Shengine::Layer
{
public:
	virtual void Init() override;
	
	virtual void Update(float dt) override;
	virtual void Draw() override;

private:
	Shengine::Renderable2D m_Renderable;
	Shengine::OrthoCamera m_Camera;
};