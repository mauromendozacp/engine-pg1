#include "game.h"

namespace GameXD
{
	float posSpeed = 0.25f;
	float rotSpeed = 0.25f;
	float scaleSpeed = 0.25f;

	Game::Game()
	{
		this->shape = NULL;
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
		shape->Init(GL::SHAPE_TYPE::TRIANGLE);
		shape->SetPos(-5.0f, 0.0f, 0.0f);
		shape->SetColor(1.0f, 1.0f, 0.0f, 0.5f);

		sprite = new GL::Sprite(render);
		/*sprite->Init("../res/Textures/izumi.png");
		sprite->SetScale(10.0f, 10.0f, 10.0f);*/

		rockstar = new GL::Sprite(render);
		rockstar->Init("../res/Textures/rock.png");
		rockstar->SetPos(5.0f, 0.0f, 0.0f);
		rockstar->SetScale(10.0f, 10.0f, 1.0f);
		rockstar->AddAnimation(2, 3, 1.0f);
	}

	void Game::Update()
	{
		Inputs();
		shape->Draw();
		//sprite->Draw();
		rockstar->Update(timer->GetDeltaTime());
		rockstar->Draw();
	}

	void Game::DeInit()
	{
		if (shape != NULL)
		{
			delete shape;
			shape = NULL;
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
			shape->SetScale(shape->GetScaleX() + scaleSpeed, shape->GetScaleY() + scaleSpeed, shape->GetScaleZ() + scaleSpeed);
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			shape->SetScale(shape->GetScaleX() - scaleSpeed, shape->GetScaleY() - scaleSpeed, shape->GetScaleZ() - scaleSpeed);
		}

		if (Collision::CheckCollision(shape, rockstar))
		{
			std::cout << "Collision!" << std::endl;
		}
	}
}