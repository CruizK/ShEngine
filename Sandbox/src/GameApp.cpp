#pragma once

#include <core/EntryPoint.h>

#include "GameLayer.h"

class GameApp : public Shengine::Application
{
public:
	GameApp() 
	{
		PushLayer(new GameLayer());
	}

	~GameApp()
	{

	}
};

Shengine::Application* CreateApplication()
{
	return new GameApp();
}