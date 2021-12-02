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
		shape->SetPos(5.0f, 0.0f, 0.0f);
		shape->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
		shape->SetMoveable(true);
		shape->SetCollider(true);
		
		rockstar = new GL::Sprite(render);
		rockstar->Init("../res/Textures/rock.png", true);
		rockstar->SetPos(0.0f, 10.0f, 0.0f);
		rockstar->SetScale(10.0f, 10.0f, 1.0f);
		rockstar->AddAnimation(2, 3, 25);
	}

	void Game::Update()
	{
		Collision::CollisionUpdate(player->GetSprite(), shape);
		player->Update(input);
	}

	void Game::Draw()
	{
		player->Draw();
		rockstar->Draw();
		//shape->Draw();
	}

	void Game::DeInit()
	{
		if (player != nullptr)
		{
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