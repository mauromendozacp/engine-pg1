#include "player.h"

namespace GameXD
{
	Player::Player()
	{
		sprite = nullptr;
		status = STATUS::IDLE;
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

		atlas = GL::AtlasConfig(6, 11, 0, 9, 1, 12);
		sprite->AddAnimation(atlas, 10.f);

		atlas = GL::AtlasConfig(6, 11, 0, 5, 1, 12);
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
		if (input->IsKeyPressed(KEY_A) || input->IsKeyPressed(KEY_LEFT))
		{
			sprite->SetPos(sprite->GetPosX() - speed, sprite->GetPosY(), sprite->GetPosZ());
			ChangeStatus(STATUS::LEFT);
		}
		else if (input->IsKeyPressed(KEY_D) || input->IsKeyPressed(KEY_RIGHT))
		{
			sprite->SetPos(sprite->GetPosX() + speed, sprite->GetPosY(), sprite->GetPosZ());
			ChangeStatus(STATUS::RIGHT);
		}
		else if (input->IsKeyPressed(KEY_W) || input->IsKeyPressed(KEY_UP))
		{
			sprite->SetPos(sprite->GetPosX(), sprite->GetPosY() + speed, sprite->GetPosZ());
			ChangeStatus(STATUS::UP);
		}
		else if (input->IsKeyPressed(KEY_S) || input->IsKeyPressed(KEY_DOWN))
		{
			sprite->SetPos(sprite->GetPosX(), sprite->GetPosY() - speed, sprite->GetPosZ());
			ChangeStatus(STATUS::DOWN);
		}
		else if (input->IsKeyPressed(KEY_Q))
		{
			sprite->SetRotZ(sprite->GetRotZ() - speed);
		}
		else if (input->IsKeyPressed(KEY_E))
		{
			sprite->SetRotZ(sprite->GetRotZ() + speed);
		}
		else if (input->IsKeyPressed(KEY_Z))
		{
			sprite->SetScale(sprite->GetScaleX() - speed, sprite->GetScaleY() - speed, sprite->GetScaleZ());
		}
		else if (input->IsKeyPressed(KEY_C))
		{
			sprite->SetScale(sprite->GetScaleX() + speed, sprite->GetScaleY() + speed, sprite->GetScaleZ());
		}
		else
		{
			ChangeStatus(STATUS::IDLE);
		}
	}

	void Player::ChangeStatus(STATUS status)
	{
		this->status = status;
		sprite->ChangeAnimation(static_cast<int>(this->status));
	}
}