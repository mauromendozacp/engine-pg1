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
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}

	void Player::Init(GL::Render* render, float speed, const char* textureUrl)
	{
		sprite = new GL::Sprite(render);
		sprite->Init(textureUrl, false);
		sprite->SetScale(5.0f, 5.0f, 1.0f);
		sprite->SetMoveable(true);
		sprite->SetCollider(true);

		GL::AtlasConfig atlas = GL::AtlasConfig(6, 11, 0, 0, 1, 18);
		sprite->AddAnimation(atlas, 10.f);

		atlas = GL::AtlasConfig(6, 11, 0, 7, 1, 12);
		sprite->AddAnimation(atlas, 10.f);

		atlas = GL::AtlasConfig(6, 11, 0, 3, 1, 12);
		sprite->AddAnimation(atlas, 10.f);

		atlas = GL::AtlasConfig(6, 11, 0, 5, 1, 12);
		sprite->AddAnimation(atlas, 10.f);

		atlas = GL::AtlasConfig(6, 11, 0, 9, 1, 12);
		sprite->AddAnimation(atlas, 10.f);

		this->speed = speed;
	}

	void Player::Update(GL::Input* input)
	{
		Inputs(input);
	}

	void Player::Draw()
	{
		sprite->Draw();
	}

	void Player::DeInit()
	{
	}

	GL::Sprite* Player::GetSprite()
	{
		return sprite;
	}

	void Player::Inputs(GL::Input* input)
	{
		if (input->IsKeyPressed(KEY_A))
		{
			sprite->SetPos(sprite->GetPosX() - speed, sprite->GetPosY(), sprite->GetPosZ());
			sprite->ChangeAnimation(1);
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			sprite->SetPos(sprite->GetPosX() + speed, sprite->GetPosY(), sprite->GetPosZ());
			sprite->ChangeAnimation(2);
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
			sprite->ChangeAnimation(4);
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			sprite->SetPos(sprite->GetPosX(), sprite->GetPosY() - speed, sprite->GetPosZ());
			sprite->ChangeAnimation(3);
		}
		else
		{
			sprite->ChangeAnimation(0);
		}
	}
}