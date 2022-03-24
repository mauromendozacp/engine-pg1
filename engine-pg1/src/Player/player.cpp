#include "player.h"

namespace GameXD
{
	Player::Player(GL::Camera* camera)
	{
		this->camera = camera;

		sprite = nullptr;
		status = STATUS::IDLE;
		moveSpeed = 0.f;
		rotSpeed = 0.f;
	}

	Player::~Player()
	{
		if (sprite != nullptr)
		{
			sprite->DeInit();
			delete sprite;
			sprite = nullptr;
		}
	}

	void Player::Init(GL::Render* render, float moveSpeed, float rotSpeed, const char* textureUrl)
	{
		sprite = new GL::Sprite(render);
		sprite->Init();
		sprite->LoadTexture(textureUrl, false);
		sprite->SetPos(0.f, 0.f, 0.f);
		sprite->SetScale(1.f, 1.f, 1.f);
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

		this->moveSpeed = moveSpeed;
		this->rotSpeed = rotSpeed;
	}

	void Player::Update()
	{
		Inputs();
		sprite->Update();
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

	void Player::Inputs()
	{
		if (GL::Input::IsKeyPressed(KEY_A) || GL::Input::IsKeyPressed(KEY_LEFT))
		{
			sprite->SetPos(GetPos() - glm::normalize(glm::cross(camera->GetFront(), camera->GetUp())) * GetSpeedDelta());
			camera->SetPosition(GetPos());
			ChangeStatus(STATUS::LEFT);
		}
		else if (GL::Input::IsKeyPressed(KEY_D) || GL::Input::IsKeyPressed(KEY_RIGHT))
		{
			sprite->SetPos(GetPos() + glm::normalize(glm::cross(camera->GetFront(), camera->GetUp())) * GetSpeedDelta());
			camera->SetPosition(GetPos());
			ChangeStatus(STATUS::RIGHT);
		}
		else if (GL::Input::IsKeyPressed(KEY_W) || GL::Input::IsKeyPressed(KEY_UP))
		{
			sprite->SetPos(GetPos() + GetSpeedDelta() * camera->GetFront());
			camera->SetPosition(GetPos());
			ChangeStatus(STATUS::UP);
		}
		else if (GL::Input::IsKeyPressed(KEY_S) || GL::Input::IsKeyPressed(KEY_DOWN))
		{
			sprite->SetPos(GetPos() - GetSpeedDelta() * camera->GetFront());
			camera->SetPosition(GetPos());
			ChangeStatus(STATUS::DOWN);
		}
		else
		{
			ChangeStatus(STATUS::IDLE);
		}

		if (GL::Input::IsKeyPressed(KEY_Q))
		{
			sprite->SetRotY(sprite->GetRotY() + rotSpeed * GL::Timer::GetDeltaTime());
		}
		else if (GL::Input::IsKeyPressed(KEY_E))
		{
			sprite->SetRotY(sprite->GetRotY() - rotSpeed * GL::Timer::GetDeltaTime());
		}

		if (GL::Input::IsKeyPressed(KEY_Z))
		{
			camera->SetCameraType(GL::CAMERA_TYPE::FPS);
			camera->SetPosition(GetPos());
		}
		else if (GL::Input::IsKeyPressed(KEY_C))
		{
			camera->SetCameraType(GL::CAMERA_TYPE::TPS);
			camera->SetPosition(GetPos());
		}

		if (GL::Input::IsKeyPressed(KEY_R))
		{
			sprite->SetPos(glm::vec3(0.f));
			camera->SetPosition(GetPos());
		}
	}

	void Player::ChangeStatus(STATUS status)
	{
		this->status = status;
		sprite->ChangeAnimation(static_cast<int>(this->status));
	}

	float Player::GetSpeedDelta()
	{
		return moveSpeed * GL::Timer::GetDeltaTime();
	}

	glm::vec3 Player::GetPos()
	{
		return sprite->GetPos();
	}
}