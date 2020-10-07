#include "GameLayer.h"
#include <gfx/Renderer2D.h>
#include <core/Application.h>
#include <input/Input.h>

void GameLayer::Init()
{
	m_Renderable.SetColor(1, 1, 1, 1);
	m_Renderable.SetScale(100);
	m_Renderable.SetPosition(100, 100);
	

	m_Camera.SetProjection(0.0f, 1280.0f, 0.0f, 720.0f, -0.1f, 100.0f);
	//m_Ortho = glm::translate(m_Ortho, glm::vec3(1280.0f / 2, 720.0f / 2, 0));
}

void GameLayer::Update(float dt)
{
	glm::vec2 direction = glm::vec2(0);

	if (Shengine::Input::IsKeyPressed(GLFW_KEY_W))
	{
		m_Camera.MoveCamera({ 0, -1 });
	}
	if (Shengine::Input::IsKeyPressed(GLFW_KEY_S))
	{
		m_Camera.MoveCamera({ 0, 1 });
	}
	if (Shengine::Input::IsKeyPressed(GLFW_KEY_A))
	{
		m_Camera.MoveCamera({ 1, 0 });
	}
	if (Shengine::Input::IsKeyPressed(GLFW_KEY_D))
	{
		m_Camera.MoveCamera({ -1, 0 });
	}

    if(Shengine::Input::IsKeyPressed(GLFW_KEY_Q))
    {
        m_Camera.SetRotation(-0.1f);
    }

    if(Shengine::Input::IsKeyPressed(GLFW_KEY_E))
    {
        m_Camera.SetRotation(0.1f);
    }

    if(Shengine::Input::IsKeyPressed(GLFW_KEY_Z))
    {
        m_Camera.SetZoom(0.01f);
    }

    if(Shengine::Input::IsKeyPressed(GLFW_KEY_X))
    {
        m_Camera.SetZoom(-0.01f);
    }

    

	glm::vec3 velocity = glm::vec3(direction.x, direction.y, 0) * dt * 500.0f;

	m_Renderable.SetPosition(m_Renderable.GetPosition() + velocity);

	//CORE_TRACE("({0},{1},{2})", m_Renderable.GetPosition().x, m_Renderable.GetPosition().y, m_Renderable.GetPosition().z);
}

void GameLayer::Draw()
{
	Shengine::Renderer2D::Begin(m_Camera);

	Shengine::Renderer2D::DrawQuad(m_Renderable);

	Shengine::Renderer2D::End();
}
