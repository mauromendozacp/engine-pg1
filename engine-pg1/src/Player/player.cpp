#include "player.h"

namespace GameXD
{
	Player::Player() : Entity3D()
	{
		camera = nullptr;
		moveSpeed = 0.f;
		rotSpeed = 0.f;
	}

	Player::Player(Render* render) : Entity3D(render)
	{
		camera = nullptr;
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
	}

	void Player::Update()
	{
		Inputs();
	}

	Camera* Player::GetCamera()
	{
		return camera;
	}

	void Player::SetCamera(CAMERA_TYPE cameraType)
	{
		if (cameraType == CAMERA_TYPE::FPS)
		{
			FirstPersonCamera* camFPS = static_cast<FirstPersonCamera*>(camera);
			camFPS->SetSpeed(5.f);
		}
		else if (cameraType == CAMERA_TYPE::TPS)
		{
			ThirdPersonCamera* camTPS = static_cast<ThirdPersonCamera*>(camera);
			camTPS->SetTarget(this);
			camTPS->SetOffset(10.f);
		}
	}

	void Player::Inputs()
	{
		if (GL::Input::IsKeyPressed(KEY_A) || GL::Input::IsKeyPressed(KEY_LEFT))
		{
			SetPos(GetPos() - glm::normalize(glm::cross(camera->GetForward(), camera->GetUp())) * GetSpeedDelta());
		}
		else if (GL::Input::IsKeyPressed(KEY_D) || GL::Input::IsKeyPressed(KEY_RIGHT))
		{
			SetPos(GetPos() + glm::normalize(glm::cross(camera->GetForward(), camera->GetUp())) * GetSpeedDelta());
		}
		else if (GL::Input::IsKeyPressed(KEY_W) || GL::Input::IsKeyPressed(KEY_UP))
		{
			SetPos(GetPos() + GetSpeedDelta() * camera->GetForward());
		}
		else if (GL::Input::IsKeyPressed(KEY_S) || GL::Input::IsKeyPressed(KEY_DOWN))
		{
			SetPos(GetPos() - GetSpeedDelta() * camera->GetForward());
		}

		if (GL::Input::IsKeyPressed(KEY_Q))
		{
			SetRotY(GetRotY() + rotSpeed * GL::Timer::GetDeltaTime());
		}
		else if (GL::Input::IsKeyPressed(KEY_E))
		{
			SetRotY(GetRotY() - rotSpeed * GL::Timer::GetDeltaTime());
		}

		if (GL::Input::IsKeyPressed(KEY_Z))
		{
			//camera->SetCameraType(GL::CAMERA_TYPE::FPS);
		}
		else if (GL::Input::IsKeyPressed(KEY_C))
		{
			//camera->SetCameraType(GL::CAMERA_TYPE::TPS);
		}

		if (GL::Input::IsKeyPressed(KEY_R))
		{
			SetPos(glm::vec3(0.f));
		}
	}

	float Player::GetSpeedDelta()
	{
		return moveSpeed * GL::Timer::GetDeltaTime();
	}
}