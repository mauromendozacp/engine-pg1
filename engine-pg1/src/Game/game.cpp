#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		floor = nullptr;
		cubeLight = nullptr;
		globalLight = nullptr;
		directionalLight = nullptr;
		pointLight = nullptr;
		spotLight = nullptr;
	}

	Game::~Game()
	{
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}
		if (floor != nullptr)
		{
			delete floor;
			floor = nullptr;
		}
		if (cubeLight != nullptr)
		{
			delete cubeLight;
			cubeLight = nullptr;
		}
		if (globalLight != nullptr)
		{
			delete globalLight;
			globalLight = nullptr;
		}
		if (directionalLight != nullptr)
		{
			delete directionalLight;
			directionalLight = nullptr;
		}
		if (pointLight != nullptr)
		{
			delete pointLight;
			pointLight = nullptr;
		}
		if (spotLight != nullptr)
		{
			delete spotLight;
			spotLight = nullptr;
		}
	}

	void Game::Init()
	{
		render->SetDepth();

		player = new Player(mainCamera);
		player->Init(render, 5.f, 75.f, "../res/Textures/player.png");

		mainCamera->SetData(player->GetSprite(), 0.25f, 10.f);
		mainCamera->SetCameraType(GL::CAMERA_TYPE::TPS);

		floor = new GL::Sprite(render);
		floor->Init(SPRITE_TYPE::QUAD);
		floor->LoadTexture("../res/Textures/floor.jpg", false);
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(50.f, 50, 1.f);

		cubeLight = new GL::Shape(render);
		cubeLight->Init(GL::SHAPE_TYPE::CUBE);
		cubeLight->SetPos(glm::vec3(15.f, 2.5f, 0.f));
		cubeLight->color.SetColor(255, 0, 0);

		globalLight = new Light(render);
		globalLight->Init();
		globalLight->color.SetColor(255, 255, 255);

		directionalLight = new DirectionalLight(render);
		directionalLight->Init();
		directionalLight->color.SetColor(44, 44, 44);
		directionalLight->SetAmbient(glm::vec3(0.75f, 0.75f, 0.75f));
		directionalLight->SetSpecular(glm::vec3(0.25f, 0.25f, 0.25f));

		pointLight = new PointLight(render);
		pointLight->Init();
		pointLight->SetPos(cubeLight->GetPos());
		pointLight->color.SetColor(255, 0, 0);
		pointLight->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
		pointLight->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
		pointLight->SetSpecular(glm::vec3(0.25f, 0.25f, 0.25f));
		pointLight->SetConstant(0.5f);
		pointLight->SetLinear(0.045f);
		pointLight->SetQuadratic(0.075f);

		spotLight = new SpotLight(render);
		spotLight->Init();
		spotLight->SetPos(glm::vec3(0.0f, 10.0f, 0.0f));
		spotLight->SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));
		spotLight->color.SetColor(255, 0, 0);
		spotLight->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
		spotLight->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
		spotLight->SetSpecular(glm::vec3(0.25f, 0.25f, 0.25f));
		spotLight->SetConstant(0.5f);
		spotLight->SetLinear(0.045f);
		spotLight->SetQuadratic(0.0075f);
		spotLight->SetCutOff(25.f);
	}

	void Game::Update()
	{
		player->Update();
		mainCamera->Update();
	}

	void Game::Draw()
	{
		floor->Draw();
		cubeLight->Draw();
		player->Draw();

		mainCamera->UseCamera();

		globalLight->UseLight();
		directionalLight->UseLight();
		pointLight->UseLight();
		spotLight->UseLight();
	}

	void Game::DeInit()
	{
		player->DeInit();
		floor->DeInit();
		cubeLight->DeInit();
	}
}