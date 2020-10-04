#pragma once

class Layer
{
public:
	Layer() {}
	virtual ~Layer() = default;

	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawImGui() = 0;

};