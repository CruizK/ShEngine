#pragma once
#include "Texture2D.h"
#include "Shader.h"
#include "Renderable2D.h"

class Renderer2D
{
public:
	
	~Renderer2D()
	{
		CORE_TRACE("BOOM BBOOM");
	}

	static void Init();
	static void Shutdown();

	static void Begin(const glm::mat4& camera);
	
	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

	static void End();

private:

};