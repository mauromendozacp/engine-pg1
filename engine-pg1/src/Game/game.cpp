#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		shape = nullptr;
	}

	Game::~Game()
	{
		if (shape != nullptr)
		{
			delete shape;
			shape = nullptr;
		}
	}

	void Game::Init()
	{
		shape = new Shape(render);
		shape->Init(SHAPE_TYPE::TRIANGLE);
		shape->SetPos(glm::vec3(0.f));
		shape->SetScale(2.5f);
		shape->SetColor(1.f, 1.f, 1.f, 1.f);
	}

	void Game::Update()
	{
		
	}

	void Game::Draw()
	{
		shape->Draw();
	}

	void Game::DeInit()
	{
	}
}