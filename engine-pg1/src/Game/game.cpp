#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		camera = nullptr;
		floor = nullptr;
		cube = nullptr;
	}

	Game::~Game()
	{
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}
		if (camera != nullptr)
		{
			delete camera;
			camera = nullptr;
		}
		if (floor != nullptr)
		{
			delete floor;
			floor = nullptr;
		}
		if (cube != nullptr)
		{
			delete cube;
			cube = nullptr;
		}
	}

	void Game::Init()
	{
		render->SetBlend();
		render->SetDepth();

		camera = new GL::Camera(render, input);
		player = new Player(camera, input, timer);
		player->Init(render, 5.f, 75.f, "../res/Textures/player.png");

		camera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		camera->SetData(player->GetPos(), 0.25f);
		camera->SetCameraType(GL::CAMERA_TYPE::TPS);
		camera->SetFocus(player->GetPos(), 10.f);

		floor = new GL::Sprite(render);
		floor->Init();
		floor->LoadTexture("../res/Textures/floor.jpg", false);
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(25.f, 25.f, 1.f);

		cube = new GL::Shape(render);
		cube->Init(GL::SHAPE_TYPE::CUBE);
		cube->SetPos(glm::vec3(5.f, 2.5f, 0.f));
		cube->SetColor(1.f, 0.f, 1.f, 1.f);
	}

	void Game::Update()
	{
		player->Update();
		camera->Update();
	}

	void Game::Draw()
	{
		floor->Draw();
		cube->Draw();
		player->Draw();
	}

	void Game::DeInit()
	{
		player->DeInit();
	}
}