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
	}

	void BaseGame::Start()
	{
		if (!glfwInit())
			return;

		window = new Window(640.0f, 480.0f, "Mauwus y Guiduwu");
		render = new Render(window);
		input = new Input(window);

		if (!window->OpenWindow())
			return;

		glfwMakeContextCurrent(window->GetWindow());

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;

		render->CreateShader();
	}

	bool BaseGame::GetWindowClose()
	{
		return glfwWindowShouldClose(window->GetWindow());
	}

	void BaseGame::ClearScreen()
	{
		render->ClearScreen();
	}

	void BaseGame::PostRender()
	{
		render->PostRender();
	}

	void BaseGame::End()
	{
		render->DeleteShader();
		window->DestroyWindow();
		glfwTerminate();
	}
}