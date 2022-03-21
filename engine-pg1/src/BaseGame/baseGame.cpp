#include "baseGame.h"

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

	void BaseGame::Play()
	{
		InitEngine();
		UpdateEngine();
		DeInitEngine();
	}

	void BaseGame::InitEngine()
	{
		if (!glfwInit())
			return;

		window = new Window(1280.0f, 720.0f, "ENGINARDOOOOUUU");
		
		if (!window->OpenWindow())
			return;

		glfwMakeContextCurrent(window->GetWindow());
		std::cout << glGetString(GL_VERSION) << std::endl;

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		render = new Render();
		input = new Input(window);
		timer = new Timer();

		render->Init();
		input->Init();

		Init();
	}

	void BaseGame::UpdateEngine()
	{
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();
			timer->Update(glfwGetTime());

			Update();
			Draw();

			render->PostRender(window);
		}
	}

	void BaseGame::DeInitEngine()
	{
		window->DestroyWindow();
		glfwTerminate();
	}
}