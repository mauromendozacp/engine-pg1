#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		shape = nullptr;
		rockstar = nullptr;
	}

	Game::~Game()
	{
	}

	void Game::Play()
	{
		InitBase();
		UpdateBase();
		DeInitBase();
	}

	void Game::Init()
	{
		player = new Player();
		player->Init(render, 0.25f, "../res/Textures/player.png");

		shape = new GL::Shape(render);
		shape->Init(GL::SHAPE_TYPE::QUAD);
		shape->SetPos(0.0f, 0.0f, 0.0f);
		shape->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
		
		rockstar = new GL::Sprite(render);
		rockstar->Init("../res/Textures/rock.png");
		rockstar->SetPos(0.0f, 10.0f, 0.0f);
		rockstar->SetScale(10.0f, 10.0f, 1.0f);
		rockstar->AddAnimation(2, 3, 2.0f);
	}

	void Game::Update()
	{
		//Collision::CollisionUpdate(shape, shape2);
		float timerF = timer->GetDeltaTime();
		player->Update(input, timerF);
		rockstar->Update(timerF);
	}

	void Game::Draw()
	{
		player->Draw();
		shape->Draw();
		rockstar->Draw();
	}

	void Game::DeInit()
	{
		if (player != nullptr)
		{
			player->DeInit();
			delete player;
			player = nullptr;
		}
		if (shape != nullptr)
		{
			delete shape;
			shape = nullptr;
		}
		if (rockstar != nullptr)
		{
			delete rockstar;
			rockstar = nullptr;
		}
	}
}