#include "game.h"

namespace GameXD
{
	float posSpeed = 0.25f;
	float rotSpeed = 0.25f;
	float scaleSpeed = 0.25f;

	Game::Game()
	{
		this->shape = nullptr;
		this->shape2 = nullptr;
		this->sprite = nullptr;
		this->rockstar = nullptr;
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
		shape2->SetPos(5.0f, 5.0f, 0.0f);
		shape2->SetScale(10.0f, 10.0f, 1.0f);
		shape2->SetColor(1.0f, 0.0f, 1.0f, 0.5f);
		shape2->SetCollider(true);
		shape2->SetMoveable(true);
	}

	void Game::Update()
	{
		Inputs();
		Collision::CollisionUpdate(shape, shape2);
		//rockstar->Update(timer->GetDeltaTime());
	}

	void Game::Draw()
	{
		shape->Draw();
		shape2->Draw();
		//sprite->Draw();
		//rockstar->Draw();
	}

	void Game::DeInit()
	{
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
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
		if (rockstar != nullptr)
		{
			delete rockstar;
			rockstar = nullptr;
		}
	}

	void Game::Inputs()
	{
		if (input->IsKeyPressed(KEY_A))
		{
			shape->SetPos(shape->GetPosX() - posSpeed, shape->GetPosY(), shape->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			shape->SetPos(shape->GetPosX() + posSpeed, shape->GetPosY(), shape->GetPosZ());
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
	}
}