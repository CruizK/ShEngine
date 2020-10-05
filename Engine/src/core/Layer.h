#pragma once

namespace Shengine {

	class Layer
	{
	public:
		Layer() {}
		virtual ~Layer() = default;

		virtual void Init() {}
		virtual void Destroy() {}
		virtual void Update(float dt) {}
		virtual void Draw() {}
		virtual void DrawImGui() {}

	};

}