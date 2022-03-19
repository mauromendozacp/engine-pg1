#include "baseGame.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = nullptr;
		render = nullptr;
		camera = nullptr;
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

		if (camera != nullptr)
		{
			delete camera;
			camera = nullptr;
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

		camera = new Camera();
		render = new Render(camera);
		input = new Input(window);
		timer = new Timer();

		render->Init(true);
		camera->Init(input, timer, 45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		camera->SetData(glm::vec3(0.f, 0.f, 25.f), 1.5f, 2.f);

		Init();
	}

	void BaseGame::UpdateEngine()
	{
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();
			timer->Update(glfwGetTime());
			camera->Update();
			//input->SetOffsetPosition(glm::vec2(0, 0));

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