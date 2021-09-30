#include "game.h"

namespace GL
{
	Game::Game()
	{
		this->entity = NULL;
	}

	Game::~Game()
	{
		if (entity != NULL)
		{
			delete entity;
			entity = NULL;
		}
	}

	void Game::Play()
	{
		Start();
		Init();
		Update();
		DeInit();
	}

	void Game::Init()
	{
		entity = new Shape(render, SHAPE_TYPE::TRIANGLE);
		entity->Init();
	}

	void Game::Update()
	{
		while (!GetWindowClose())
		{
			ClearScreen();

			//****Render here****
			entity->Draw();
			//--------------------

			PostRender();
		}
	}

	void Game::DeInit()
	{
		End();
	}
}