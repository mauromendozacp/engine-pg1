#include "game.h"

namespace GameXD
{
	float posSpeed = 1.0f;
	float rotSpeed = 1.0f;
	float scaleSpeed = 1.0f;

	Game::Game()
	{
		this->shape = NULL;
	}

	Game::~Game()
	{
		if (shape != NULL)
		{
			delete shape;
			shape = NULL;
		}
	}

	void Game::Play()
	{
		Start();
		Init();
		Update();
		DeInit();
	}

	void Game::Inputs()
	{
		if (input->IsKeyPressed(KEY_A))
		{
			shape->SetPos(shape->GetPosX() + posSpeed, shape->GetPosY(), shape->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			shape->SetPos(shape->GetPosX() - posSpeed, shape->GetPosY(), shape->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_Q))
		{
			shape->SetRotZ(shape->GetRotZ() - rotSpeed);
		}
		else if (input->IsKeyPressed(KEY_E))
		{
			shape->SetRotZ(shape->GetRotZ() + rotSpeed);
		}
		else if (input->IsKeyPressed(KEY_W))
		{
			shape->SetScale(shape->GetScaleX() + scaleSpeed, shape->GetScaleY() + scaleSpeed, shape->GetScaleZ() + scaleSpeed);
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			shape->SetScale(shape->GetScaleX() - scaleSpeed, shape->GetScaleY() - scaleSpeed, shape->GetScaleZ() - scaleSpeed);
		}
	}

	void Game::Init()
	{
		shape = new GL::Shape(render, GL::SHAPE_TYPE::TRIANGLE);
		shape->Init();
	}

	void Game::Update()
	{
		while (!GetWindowClose())
		{
			ClearScreen();

			Inputs();

			//****Render here****
			shape->Draw();
			//--------------------

			PostRender();
		}
	}

	void Game::DeInit()
	{
		End();
	}
}