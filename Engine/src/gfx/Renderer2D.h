#pragma once
#include "Font.h"
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
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, const glm::vec4& tintColor);
		static void DrawString(const glm::mat4 transform, const Ref<Font> font, const std::string& text, const glm::vec4& color);

		static void End();

	private:
		static void Flush();
		static void FlushAndReset();
	};
}