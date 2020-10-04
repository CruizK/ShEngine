#pragma once

#include <core/EntryPoint.h>

class GameApp : public Application
{
public:
	GameApp() 
	{
		
	}

	~GameApp()
	{

	}
};

Application* CreateApplication()
{
	return new GameApp();
}