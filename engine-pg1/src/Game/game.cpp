#include "game.h"
#include "Shape/shape.h"
#include "Renderer/renderer.h"
#include "Input/input.h"

namespace GL
{
	Game::Game()
	{
		this->entity = NULL;
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

		input->Init();
	}

	void Game::Init()
	{
		float vertices[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
		};
		unsigned int indices[] = {
			0, 1, 3
		};

		render->CreateShader();
		
		entity = new Shape(render, SHAPE_TYPE::TRIANGLE);
	}

	void Game::Update()
	{
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();

			//****Render here****
			
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