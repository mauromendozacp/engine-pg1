#include "game.h"

namespace GL
{
	Game::Game()
	{
	}

	Game::~Game()
	{
	}

	void Game::Play()
	{
		Start();
		Init();
		Update();
		DeInit();
	}

	void Game::Start() 
	{
		if (!glfwInit())
			return;

		if (!window->OpenWindow())
			return;

		glfwMakeContextCurrent(window->GetWindow());

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;
	}

	void Game::Init()
	{
		render->CreateShader();
		render->RenderBufferTriangule();
	}

	void Game::Update()
	{
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();

			//****Render here****
			render->Draw();
			//--------------------

			render->PostRender();
		}
	}

	void Game::DeInit()
	{
		render->DeleteShader();
		glfwTerminate();
	}
}