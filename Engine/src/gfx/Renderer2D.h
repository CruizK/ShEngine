#pragma once
#include "Texture2D.h"
#include "Shader.h"
#include "Renderable2D.h"
#include "OrthoCamera.h"

namespace Shengine {
	class Renderer2D
	{
	public:

		~Renderer2D()
		{
			CORE_TRACE("BOOM BBOOM");
		}

		static void Init();
		static void Shutdown();

		static void Begin(const OrthoCamera& camera);

		static void DrawQuad(const Renderable2D& renderable);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D> texture, const glm::vec4& tintColor);

		static void End();

	private:
		static void Flush();
		static void FlushAndReset();
	};
}