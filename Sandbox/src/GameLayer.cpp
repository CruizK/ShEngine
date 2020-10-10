#include "GameLayer.h"
#include <gfx/Renderer2D.h>
#include <core/Application.h>
#include <input/Input.h>

GameLayer::GameLayer() 
    : m_CameraController(1280, 720)
{

}

void GameLayer::Init()
{
	m_Renderable.SetColor(1, 1, 1, 1);
	m_Renderable.SetScale(100);
	m_Renderable.SetPosition(100, 100);
	

	//m_Camera.SetProjection(0.0f, 1280.0f, 0.0f, 720.0f);
	//m_Ortho = glm::translate(m_Ortho, glm::vec3(1280.0f / 2, 720.0f / 2, 0));
}

void GameLayer::Update(float dt)
{
	glm::vec2 direction = glm::vec2(0);

    m_CameraController.Update(dt);

	glm::vec3 velocity = glm::vec3(direction.x, direction.y, 0) * dt * 500.0f;

	m_Renderable.SetPosition(m_Renderable.GetPosition() + velocity);

	//CORE_TRACE("({0},{1},{2})", m_Renderable.GetPosition().x, m_Renderable.GetPosition().y, m_Renderable.GetPosition().z);
}

void GameLayer::Draw()
{
	Shengine::Renderer2D::Begin(m_CameraController.GetCamera());

	Shengine::Renderer2D::DrawQuad(m_Renderable);

	Shengine::Renderer2D::End();
}
