#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		floor = nullptr;
		cubeLight = nullptr;
		directionalLight = nullptr;
	}

	Game::~Game()
	{
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}
		if (floor != nullptr)
		{
			delete floor;
			floor = nullptr;
		}
		if (cubeLight != nullptr)
		{
			delete cubeLight;
			cubeLight = nullptr;
		}
		if (directionalLight != nullptr)
		{
			delete directionalLight;
			directionalLight = nullptr;
		}
	}

	void Game::Init()
	{
		render->SetBlend();
		render->SetDepth();

		player = new Player(mainCamera);
		player->Init(render, 5.f, 75.f, "../res/Textures/player.png");

		mainCamera->SetData(player->GetSprite(), 0.25f, 10.f);
		mainCamera->SetCameraType(GL::CAMERA_TYPE::TPS);

		floor = new GL::Sprite(render);
		floor->Init();
		floor->LoadTexture("../res/Textures/floor.jpg", false);
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(25.f, 25.f, 1.f);

		cubeLight = new GL::Shape(render);
		cubeLight->Init(GL::SHAPE_TYPE::CUBE);
		cubeLight->SetPos(glm::vec3(5.f, 2.5f, 0.f));
		cubeLight->color.SetColor(255, 0, 0);

		directionalLight = new DirectionalLight(render);
		directionalLight->Init();
		directionalLight->SetColor(glm::vec3(0.55f, 0.42f, 0.18f));
		directionalLight->SetAmbient(glm::vec3(0.75f, 0.75f, 0.75f));
		directionalLight->SetSpecular(glm::vec3(0.25f, 0.25f, 0.25f));
	}

	void Game::Update()
	{
		player->Update();
		mainCamera->Update();
	}

	void Game::Draw()
	{
		floor->Draw();
		cubeLight->Draw();
		player->Draw();

		mainCamera->UseCamera();
		directionalLight->UseLight();
	}

	void Game::DeInit()
	{
		player->DeInit();
		floor->DeInit();
	}
}