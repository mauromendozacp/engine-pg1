#include "baseGame.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = new Window(640, 480, "Hello World");
		//window = nullptr;
	}

	BaseGame::~BaseGame()
	{
		if (window != nullptr) 
		{
			window = nullptr;
			delete window;
		}
	}

	void BaseGame::Play()
	{
		Init();

		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			Update();
		}

		DeInit();
	}

	void BaseGame::Init()
	{
		if (!glfwInit())
			return;

		if (!window->OpenWindow())
			return;

		glfwMakeContextCurrent(window->GetWindow());
	}

	void BaseGame::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}

	void BaseGame::DeInit()
	{
		glfwTerminate();
	}
}