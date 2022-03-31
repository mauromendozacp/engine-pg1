#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		floor = nullptr;
		cubeLight = nullptr;
		spotCubeLight = nullptr;
		tnt = nullptr;
		defaultMaterial = nullptr;
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
		if (spotCubeLight != nullptr)
		{
			delete spotCubeLight;
			spotCubeLight = nullptr;
		}
		if (defaultMaterial != nullptr)
		{
			delete defaultMaterial;
			defaultMaterial = nullptr;
		}
		if (tnt != nullptr)
		{
			delete tnt;
			tnt = nullptr;
		}
	}

	void Game::Init()
	{
		render->SetDepth();

		player = new Player(mainCamera);
		player->Init(render, 5.f, 75.f, "../res/Textures/player.png");

		mainCamera->SetData(player->GetSprite(), 0.25f, 10.f);
		mainCamera->SetCameraType(GL::CAMERA_TYPE::TPS);

		floor = new Sprite(render);
		floor->Init(SPRITE_TYPE::QUAD);
		floor->LoadTexture("../res/Textures/floor.jpg", false);
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(50.f, 50, 1.f);

		cubeLight = new Shape(render);
		cubeLight->Init(SHAPE_TYPE::CUBE);
		cubeLight->SetPos(glm::vec3(15.f, 2.5f, 0.f));
		cubeLight->color.SetColor(0, 255, 0);
		
		spotCubeLight = new Shape(render);
		spotCubeLight->Init(SHAPE_TYPE::CUBE);
		spotCubeLight->SetPos(glm::vec3(0.f, 5.f, 0.f));
		spotCubeLight->color.SetColor(255, 0, 0);
		spotCubeLight->SetScale(0.75f);

		tnt = new Sprite(render);
		tnt->Init(SPRITE_TYPE::CUBE);
		tnt->LoadTexture("../res/Textures/tnt.png", true);
		tnt->SetPos(glm::vec3(10.f, .5f, 10.f));

		defaultMaterial = new Material(render);
		defaultMaterial->Init();
		defaultMaterial->SetShininess(32.f);
		defaultMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		defaultMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultMaterial->UpdateShader();

		lightManager->AddLight(LIGHT_TYPE::DIRECTIONAL);
		DirectionalLight* directionalLight = lightManager->GetDirectionalLight();
		directionalLight->Init();
		directionalLight->color.SetColor(240, 240, 240);
		directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
		directionalLight->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		directionalLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		directionalLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

		lightManager->AddLight(LIGHT_TYPE::POINTLIGHT);
		PointLight* pointLight = lightManager->GetLasPointLightCreated();
		pointLight->SetPos(cubeLight->GetPos() + glm::vec3(0.f, 2.5f, 0.f));
		pointLight->color = cubeLight->color;
		pointLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
		pointLight->SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
		pointLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		pointLight->SetConstant(1.f);
		pointLight->SetLinear(0.09f);
		pointLight->SetQuadratic(0.032f);

		lightManager->AddLight(LIGHT_TYPE::SPOTLIGHT);
		SpotLight* spotLight = lightManager->GetLasSpotLightCreated();
		spotLight->SetPos(spotCubeLight->GetPos());
		spotLight->SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));
		spotLight->color = spotCubeLight->color;
		spotLight->SetAmbient(glm::vec3(1.f, 1.f, 1.f));
		spotLight->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
		spotLight->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
		spotLight->SetConstant(1.f);
		spotLight->SetLinear(0.1f);
		spotLight->SetQuadratic(0.032f);
		spotLight->SetCutOff(25.f);
		spotLight->SetOuterCutOff(15.f);
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
		spotCubeLight->Draw();
		tnt->Draw();
		player->Draw();

		mainCamera->UseCamera();
	}

	void Game::DeInit()
	{
		player->DeInit();
		floor->DeInit();
		cubeLight->DeInit();
		spotCubeLight->DeInit();
		tnt->DeInit();
	}
}