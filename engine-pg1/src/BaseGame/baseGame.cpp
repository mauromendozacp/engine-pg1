#include "baseGame.h"

#include "Renderer/renderer.h"
#include "Input/input.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = nullptr;
		render = nullptr;
		input = nullptr;
		timer = nullptr;
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

		if (input != nullptr)
		{
			delete input;
			input = nullptr;
		}

		if (timer != nullptr)
		{
			delete timer;
			timer = nullptr;
		}
	}

	void BaseGame::InitBase()
	{
		if (!glfwInit())
			return;

		window = new Window(640.0f, 480.0f, "COCO 2, LA VENGANZA ANASHEEEE");
		
		if (!window->OpenWindow())
			return;

		glfwMakeContextCurrent(window->GetWindow());

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		render = new Render();
		input = new Input(window);
		timer = new Timer();

		std::cout << glGetString(GL_VERSION) << std::endl;

		render->InitShader();

		Init();
	}

	void BaseGame::UpdateBase()
	{
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();
			timer->Update();

			Update();
			Draw();

			render->PostRender(window);
		}
	}

	void BaseGame::DeInitBase()
	{
		window->DestroyWindow();
		glfwTerminate();
	}
}