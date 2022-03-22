#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		camera = nullptr;
		floor = nullptr;
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
	}

	void Game::Init()
	{
		render->SetDepth();

		camera = new GL::Camera(render, input);
		player = new Player(camera, input, timer);
		player->Init(render, 5.f, "../res/Textures/player.png");

		camera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		camera->SetData(player->GetPos(), 0.25f);
		camera->SetCameraType(GL::CAMERA_TYPE::TPS);
		camera->SetFocus(player->GetPos(), 10.f);

		floor = new GL::Shape(render);
		floor->Init(GL::SHAPE_TYPE::QUAD);
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.F);
		floor->SetScale(25.f, 25.f, 1.f);
		floor->SetColor(0.f, 1.f, 1.f, 1.f);
	}

	void Game::Update()
	{
		player->Update();
		camera->Update();
	}

	void Game::Draw()
	{
		player->Draw();
		floor->Draw();
	}

	void Game::DeInit()
	{
		player->DeInit();
	}
}