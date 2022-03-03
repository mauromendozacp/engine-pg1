#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		shape = nullptr;
		shape2 = nullptr;
		rockstar = nullptr;
		tileMap = nullptr;
	}

	Game::~Game()
	{
	}

	void Game::Init()
	{
		player = new Player();
		player->Init(render, 1.f, "../res/Textures/player.png");

		/*shape = new Shape(render);
		shape->Init(SHAPE_TYPE::TRIANGLE);
		shape->SetPos(65.0f, 0.0f, 0.0f);
		shape->SetColor(0.0f, 0.0f, 1.0f, 0.5f);
		shape->SetScale(20.f, 20.f, 10.f);*/

		/*shape2 = new Shape(render);
		shape2->Init(SHAPE_TYPE::QUAD);
		shape2->SetPos(-65.0f, 0.0f, 0.0f);
		shape2->SetColor(1.0f, 0.0f, 1.0f, 1.0f);
		shape2->SetScale(20.f, 20.f, 10.f);*/
		
		rockstar = new Sprite(render);
		rockstar->Init();
		rockstar->LoadTexture("../res/Textures/rock.png", true);
		rockstar->SetPos(0.0f, 10.0f, 0.0f);
		rockstar->SetScale(8.f, 8.f, 1.0f);
		rockstar->AddAnimation(2, 3, 25);

		tileMap = new Tilemap(render);
		tileMap->ImportTileMap("../res/Tiled/engine1_test.tmx", "../res/Textures/tileset.png");
		tileMap->SetSize(0.5f);
	}

	void Game::Update()
	{
		/*Collision::CollisionUpdate(shape, player->GetSprite());
		Collision::CollisionUpdate(shape2, player->GetSprite());*/
		player->Update(input);
		tileMap->CheckCollision(player->GetSprite());
	}

	void Game::Draw()
	{
		tileMap->Draw();
		rockstar->Draw();
		/*shape->Draw();
		shape2->Draw();*/
		player->Draw();
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
			shape->DeInit();
			delete shape;
			shape = nullptr;
		}
		if (shape2 != nullptr)
		{
			shape2->DeInit();
			delete shape2;
			shape2 = nullptr;
		}
		if (rockstar != nullptr)
		{
			rockstar->DeInit();
			delete rockstar;
			rockstar = nullptr;
		}
		if (tileMap != nullptr)
		{
			tileMap->DeInit();
			delete tileMap;
			tileMap = nullptr;
		}
	}
}