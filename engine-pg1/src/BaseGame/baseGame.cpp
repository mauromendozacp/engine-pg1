#include "baseGame.h"

#include "Renderer/renderer.h"
#include "Input/input.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = NULL;
		render = NULL;
		input = NULL;
		timer = NULL;
	}

	BaseGame::~BaseGame()
	{
		if (window != NULL) 
		{
			delete window;
			window = NULL;
		}

		if (render != NULL)
		{
			delete render;
			render = NULL;
		}

		if (input != NULL)
		{
			delete input;
			input = NULL;
		}

		if (timer != NULL)
		{
			delete timer;
			timer = NULL;
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
			render->PostRender(window);
		}
	}

	void BaseGame::DeInitBase()
	{
		window->DestroyWindow();
		glfwTerminate();
	}
}