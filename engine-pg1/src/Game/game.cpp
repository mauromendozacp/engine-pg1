#include "game.h"

namespace GameXD
{
	float posSpeed = 0.25f;
	float rotSpeed = 0.25f;
	float scaleSpeed = 0.25f;

	Game::Game()
	{
		this->shape = NULL;
		this->shape2 = NULL;
		this->sprite = NULL;
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
		shape = new GL::Shape(render);
		shape->Init(GL::SHAPE_TYPE::QUAD);
		shape->SetPos(0.0f, 0.0f, 0.0f);
		shape->SetColor(1.0f, 1.0f, 0.0f, 0.5f);

		sprite = new GL::Sprite(render);
		/*sprite->Init("../res/Textures/izumi.png");
		sprite->SetScale(10.0f, 10.0f, 10.0f);*/
		/*
		rockstar = new GL::Sprite(render);
		rockstar->Init("../res/Textures/rock.png");
		rockstar->SetPos(0.0f, 0.0f, 0.0f);
		rockstar->SetScale(10.0f, 10.0f, 1.0f);
		rockstar->AddAnimation(2, 3, 1.0f);*/

		shape2 = new GL::Shape(render);
		shape2->Init(GL::SHAPE_TYPE::QUAD);
		shape2->SetPos(0.0f, 0.0f, 0.0f);
		shape2->SetScale(10.0f, 10.0f, 1.0f);
		shape2->SetColor(1.0f, 0.0f, 1.0f, 0.5f);
	}

	void Game::Update()
	{
		Inputs();
		shape->Draw();
		shape2->Draw();
		//sprite->Draw();
		//rockstar->Update(timer->GetDeltaTime());
		//rockstar->Draw();
	}

	void Game::DeInit()
	{
		if (shape != NULL)
		{
			delete shape;
			shape = NULL;
		}
		if (shape2 != NULL)
		{
			delete shape2;
			shape2 = NULL;
		}
		if (sprite != NULL)
		{
			delete sprite;
			sprite = NULL;
		}
		if (rockstar != NULL)
		{
			delete rockstar;
			rockstar = NULL;
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
			//shape->SetScale(shape->GetScaleX() + scaleSpeed, shape->GetScaleY() + scaleSpeed, shape->GetScaleZ() + scaleSpeed);
			shape->SetPos(shape->GetPosX(), shape->GetPosY() + posSpeed, shape->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			shape->SetPos(shape->GetPosX(), shape->GetPosY() - posSpeed, shape->GetPosZ());
			//shape->SetScale(shape->GetScaleX() - scaleSpeed, shape->GetScaleY() - scaleSpeed, shape->GetScaleZ() - scaleSpeed);
		}
		
		if (Collision::CheckCollisionRecRec(shape, shape2))
		{
			std::cout << "Collision!" << std::endl;

			Collision::Overlap(shape, shape2);
		}
		
	}
}