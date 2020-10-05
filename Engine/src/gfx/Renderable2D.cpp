#include "Renderable2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Shengine {

	Renderable2D::Renderable2D()
		: m_Position(glm::vec3(0.0f)), m_Scale(glm::vec2(1.0f)), m_Color(glm::vec4(1.0f)), m_Transform(glm::mat4(1.0f))
	{
	}

	Renderable2D::~Renderable2D()
	{
	}

	void Renderable2D::SetPosition(const glm::vec2& pos)
	{
		SetPosition(pos.x, pos.y, 0);
	}

	void Renderable2D::SetPosition(const glm::vec3& pos)
	{
		SetPosition(pos.x, pos.y, pos.z);
	}

	void Renderable2D::SetPosition(float x, float y)
	{
		SetPosition(x, y, 0);
	}

	void Renderable2D::SetPosition(float x, float y, float z)
	{
		m_Position = glm::vec3(x, y, z);
		UpdateTransform();
	}

	void Renderable2D::SetScale(const glm::vec2& scale)
	{
		SetScale(scale.x, scale.y);
	}

	void Renderable2D::SetScale(float value)
	{
		SetScale(value, value);
	}

	void Renderable2D::SetScale(float x, float y)
	{
		m_Scale = glm::vec2(x, y);
		UpdateTransform();
	}

	void Renderable2D::SetColor(const glm::vec4& color)
	{
		SetColor(color.r, color.g, color.b, color.a);
	}

	void Renderable2D::SetColor(float r, float g, float b, float a)
	{
		m_Color = glm::vec4(r, g, b, a);
	}

	void Renderable2D::UpdateTransform()
	{
		m_Transform = glm::mat4(1.0f);

		m_Transform =
			glm::translate(m_Transform, m_Position) *
			glm::scale(m_Transform, glm::vec3(m_Scale.x, m_Scale.y, 1));
	}
}