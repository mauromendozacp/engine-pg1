#include "baseGame.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = new Window(640, 480, "Hello World");
	}

	BaseGame::~BaseGame()
	{
		delete window;
	}

	void BaseGame::Init()
	{
		if (!window->OpenWindow())
		{
			return;
		}

		glfwMakeContextCurrent(window->GetWindow());
	}

	void BaseGame::Update()
	{

	}

	void BaseGame::Draw()
	{

	}

	void BaseGame::DeInit()
	{
	}


}