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
		//player->Init(render, 0.25f, "../res/Textures/player.png");

		shape = new Shape(render);
		shape->Init(SHAPE_TYPE::TRIANGLE);
		shape->SetPos(5.0f, 0.0f, 0.0f);
		shape->SetColor(0.0f, 0.0f, 1.0f, 0.5f);
		shape->SetMoveable(true);
		shape->SetCollider(true);

		shape2 = new Shape(render);
		shape2->Init(SHAPE_TYPE::QUAD);
		shape2->SetPos(-5.0f, 0.0f, 0.0f);
		shape2->SetColor(1.0f, 0.0f, 1.0f, 1.0f);
		shape2->SetMoveable(true);
		shape2->SetCollider(true);
		
		rockstar = new Sprite(render);
		/*rockstar->Init();
		rockstar->LoadTexture("../res/Textures/rock.png", true);
		rockstar->SetPos(0.0f, 10.0f, 0.0f);
		rockstar->SetScale(10.0f, 10.0f, 1.0f);
		rockstar->AddAnimation(2, 3, 25);*/

		tileMap = new Tilemap(render);
		tileMap->ImportTileMap("../res/Tiled/engine1_test.xml", "../res/Textures/tileset.png");
		//tileMap->SetDimentions(15.f, 15.f);
	}

	void Game::Update()
	{
		/*Collision::CollisionUpdate(player->GetSprite(), shape);
		Collision::CollisionUpdate(player->GetSprite(), shape2);
		player->Update(input);*/
	}

	void Game::Draw()
	{
		//rockstar->Draw();
		//player->Draw();
		shape->Draw();
		shape2->Draw();
		tileMap->Draw();
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
		if (shape2 != nullptr)
		{
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
			delete tileMap;
			tileMap = nullptr;
		}
	}
}