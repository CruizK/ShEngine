#pragma once

#include <core/EntryPoint.h>

class GameApp : public Shengine::Application
{
public:
	GameApp() 
	{
		
	}

	~GameApp()
	{

	}
};

Shengine::Application* CreateApplication()
{
	return new GameApp();
}