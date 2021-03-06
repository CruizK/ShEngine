#pragma once

#include <core/Layer.h>
#include <gfx/Renderable2D.h>
#include <gfx/Renderer2D.h>
#include <gfx/OrthoCameraController.h>
#include <gfx/Font.h>

class GameLayer : public Shengine::Layer
{
public:
    GameLayer();

	virtual void Init() override;
	
	virtual void Update(float dt) override;
	virtual void Draw() override;

private:
	Shengine::Renderable2D m_Renderable;
    Shengine::OrthoCameraController m_CameraController;
	Shengine::Ref<Shengine::Font> m_Font;
	Shengine::Ref<Shengine::Texture2D> m_Texture;
};