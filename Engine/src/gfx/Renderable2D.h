#pragma once

#include <glm/glm.hpp>

namespace Shengine {

	class Renderable2D
	{
	public:
		Renderable2D();
		~Renderable2D();


		void SetPosition(const glm::vec2& pos);
		void SetPosition(const glm::vec3& pos);
		void SetPosition(float x, float y);
		void SetPosition(float x, float y, float z);



		void SetScale(const glm::vec2& scale);
		void SetScale(float value);
		void SetScale(float x, float y);

		// TODO: Make color struct that is a single unsigned int
		void SetColor(const glm::vec4& color);
		void SetColor(float r, float g, float b, float a);

		inline const glm::mat4& GetTransform() const { return m_Transform; }
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec2& GetScale() const { return m_Scale; }
		inline const glm::vec4& GetColor() const { return m_Color; }

	private:
		glm::mat4 m_Transform;
		glm::vec3 m_Position;
		glm::vec2 m_Scale;
		glm::vec4 m_Color;

	private:
		void UpdateTransform();
	};
}