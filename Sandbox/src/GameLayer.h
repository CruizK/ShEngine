#pragma once

#include <core/Layer.h>
#include <gfx/Renderable2D.h>
#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public Shengine::Layer
{
public:
	virtual void Init() override;
	
	virtual void Update(float dt) override;
	virtual void Draw() override;

private:
	Shengine::Renderable2D m_Renderable;
	glm::mat4 m_Ortho;
};