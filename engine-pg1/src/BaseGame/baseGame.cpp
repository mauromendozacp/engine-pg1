#include "baseGame.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = nullptr;
		render = nullptr;
		mainCamera = nullptr;
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

		if (mainCamera != nullptr)
		{
			delete mainCamera;
			mainCamera = nullptr;
		}

		if (lightManager != nullptr)
		{
			delete lightManager;
			lightManager = nullptr;
		}
	}

	void BaseGame::Play()
	{
		if (!glfwInit())
		{
			std::cout << "GLFW Initialization failed" << std::endl;
			glfwTerminate();
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = new Window(1280.0f, 720.0f, "ENGINARDOOOOUUU");
		if (!window->OpenWindow())
			return;

		InitEngine();
		UpdateEngine();
		DeInitEngine();
	}

	void BaseGame::InitEngine()
	{
		window->Init();

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		render = new Render();
		mainCamera = new Camera(render);
		lightManager = new LightManager();

		render->Init();
		mainCamera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		lightManager->Init(render);
		Input::Init(window, mainCamera);

		Init();
	}

	void BaseGame::UpdateEngine()
	{
		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			render->ClearScreen();
			Timer::Update(glfwGetTime());

			Update();
			Draw();

			lightManager->UseLights();
			render->PostRender(window);
		}
	}

	void BaseGame::DeInitEngine()
	{
		window->DestroyWindow();
		glfwTerminate();
	}
}