#include "player.h"

namespace GameXD
{
	Player::Player() : Entity3D()
	{
		camera = nullptr;
		moveBaseSpeed = 0.f;
		moveSpeed = 0.f;
		rotSpeed = 0.f;
	}

	Player::Player(Render* render) : Entity3D(render)
	{
		camera = nullptr;
		moveBaseSpeed = 0.f;
		moveSpeed = 0.f;
		rotSpeed = 0.f;
	}

	Player::~Player()
	{
	}

	void Player::Init(Camera* camera, float moveSpeed, float rotSpeed)
	{
		this->camera = camera;
		this->moveSpeed = moveSpeed;
		this->rotSpeed = rotSpeed;

		moveBaseSpeed = moveSpeed;
	}

	void Player::Update()
	{
		Inputs();
	}

	void Player::Inputs()
	{
		if (Input::IsKeyPressed(KEY_A) || Input::IsKeyPressed(KEY_LEFT))
		{
			SetPos(GetPos() - glm::normalize(glm::cross(camera->GetForward(), camera->GetUp())) * GetSpeedDelta());
		}
		else if (Input::IsKeyPressed(KEY_D) || Input::IsKeyPressed(KEY_RIGHT))
		{
			SetPos(GetPos() + glm::normalize(glm::cross(camera->GetForward(), camera->GetUp())) * GetSpeedDelta());
		}
		else if (Input::IsKeyPressed(KEY_W) || GL::Input::IsKeyPressed(KEY_UP))
		{
			SetPos(GetPos() + GetSpeedDelta() * camera->GetForward());
		}
		else if (Input::IsKeyPressed(KEY_S) || GL::Input::IsKeyPressed(KEY_DOWN))
		{
			SetPos(GetPos() - GetSpeedDelta() * camera->GetForward());
		}

		if (GL::Input::IsKeyPressed(KEY_Q))
		{
			camera->SetFollowStatus(true);
		}
		else if (GL::Input::IsKeyPressed(KEY_E))
		{
			camera->SetFollowStatus(false);
		}

		if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
		{
			moveSpeed = moveBaseSpeed * 2.5f;
		}
		else
		{
			moveSpeed = moveBaseSpeed;
		}
	}

	float Player::GetSpeedDelta()
	{
		return moveSpeed * Timer::GetDeltaTime();
	}
}