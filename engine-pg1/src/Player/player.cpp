#include "player.h"

namespace GameXD
{
	Player::Player()
	{
		sprite = nullptr;
		speed = 0.0f;
	}

	Player::~Player()
	{
	}

	void Player::Init(GL::Render* render, float speed, std::string textureUrl)
	{
		sprite = new GL::Sprite(render);
		sprite->Init(textureUrl);
		sprite->SetPos(0.0f, 0.0f, 0.0f);
		sprite->SetScale(5.0f, 5.0f, 1.0f);

		sprite->AddAnimation(3, 6, 1.0f);

		this->speed = speed;
	}

	void Player::Update(GL::Input* input, float timer)
	{
		Inputs(input);
		sprite->Update(timer);
	}

	void Player::Draw()
	{
		sprite->Draw();
	}

	void Player::DeInit()
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}

	void Player::Inputs(GL::Input* input)
	{
		if (input->IsKeyPressed(KEY_A))
		{
			sprite->SetPos(sprite->GetPosX() - speed, sprite->GetPosY(), sprite->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			sprite->SetPos(sprite->GetPosX() + speed, sprite->GetPosY(), sprite->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_Q))
		{
			sprite->SetRotZ(sprite->GetRotZ() - speed);
		}
		else if (input->IsKeyPressed(KEY_E))
		{
			sprite->SetRotZ(sprite->GetRotZ() + speed);
		}
		else if (input->IsKeyPressed(KEY_W))
		{
			sprite->SetPos(sprite->GetPosX(), sprite->GetPosY() + speed, sprite->GetPosZ());
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			sprite->SetPos(sprite->GetPosX(), sprite->GetPosY() - speed, sprite->GetPosZ());
		}
	}
}