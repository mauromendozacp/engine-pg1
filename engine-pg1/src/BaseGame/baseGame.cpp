#include "baseGame.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = nullptr;
		render = nullptr;
		mainCamera = nullptr;
		lightManager = nullptr;
		terminateEngine = false;
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

		InitEngine();
		UpdateEngine();
		DeInitEngine();
	}

	void BaseGame::InitEngine()
	{
		window = new Window(1280.0f, 720.0f, "ENGINARDOOOOUUU");
		if (!window->OpenWindow())
			return;

		window->Init();

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR" << std::endl;

		render = new Render();
		render->Init();

		lightManager = new LightManager(render);

		mainCamera = new ThirdPersonCamera(render);
		mainCamera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		mainCamera->SetSensitivity(0.25f);

		Input::Init(window, mainCamera);

		OcclusionCulling::Init(mainCamera);		

		srand(time(NULL));

		Init();
	}

	void BaseGame::UpdateEngine()
	{
		while (!glfwWindowShouldClose(window->GetWindow()) && !terminateEngine)
		{
			render->ClearScreen();
			Timer::Update(glfwGetTime());

			Update();
			OcclusionCulling::Update();
			lightManager->UseLights();
			Draw();

			render->PostRender(window);
		}
	}

	void BaseGame::DeInitEngine()
	{
		window->DestroyWindow();
		glfwTerminate();
	}

	void BaseGame::CloseEngine()
	{
		terminateEngine = true;
	}
}