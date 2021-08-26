#include "baseGame.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = new Window(640, 480, "Hello World");
		render = new Render(window);
	}

	BaseGame::~BaseGame()
	{
		if (window != nullptr) 
		{
			delete window;
			window = nullptr;
		}

		if (render != nullptr)
		{
			delete render;
			render = nullptr;
		}
	}

	void BaseGame::Play()
	{
		Init();
		Update();
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
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();

			//****Render here****
			render->RenderTriangule();
			//--------------------

			render->PostRender();
		}
	}

	void BaseGame::DeInit()
	{
		glfwTerminate();
	}
}