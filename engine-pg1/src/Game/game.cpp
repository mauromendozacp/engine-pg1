#include "game.h"

namespace GameXD
{
	float posSpeed = 0.25f;
	float rotSpeed = 0.25f;
	float scaleSpeed = 0.25f;

	Game::Game()
	{
		this->shape = NULL;
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
		shape = new GL::Shape(render, GL::SHAPE_TYPE::TRIANGLE);
		shape->Init();
		shape->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	}

	void Game::Update()
	{
		Inputs();
		shape->Draw();
	}

	void Game::DeInit()
	{
		if (shape != NULL)
		{
			delete shape;
			shape = NULL;
		}
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
}