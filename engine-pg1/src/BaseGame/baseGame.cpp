#include "baseGame.h"

#include "Renderer/renderer.h"
#include "Input/input.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = new Window(640, 480, "Hello World");
		render = new Render(window);
		input = new Input(window);
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

		if (!window->OpenWindow())
			return;

		glfwMakeContextCurrent(window->GetWindow());

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;

		input->Init();
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
		glfwTerminate();
	}
}