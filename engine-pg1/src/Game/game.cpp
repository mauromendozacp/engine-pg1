#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;
		floor = nullptr;
		
		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i] = nullptr;
		}

		spotCubeLight = nullptr;
		tnt = nullptr;
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

		for (int i = 0; i < cubesLenght; i++)
		{
			if (cubeLight[i] != nullptr)
			{
				delete cubeLight[i];
				cubeLight[i] = nullptr;
			}
		}
		
		if (spotCubeLight != nullptr)
		{
			delete spotCubeLight;
			spotCubeLight = nullptr;
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

		Material* defaultMaterial = new Material(render);
		defaultMaterial->Init();
		defaultMaterial->SetShininess(32.f);
		defaultMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		defaultMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultMaterial->UpdateShader();

		player = new Player(mainCamera);
		player->Init(render, defaultMaterial, 5.f, 75.f, "../res/Textures/player.png");

		mainCamera = new ThirdPersonCamera(render);
		ThirdPersonCamera* cam = static_cast<ThirdPersonCamera*>(mainCamera);
		cam->SetTarget(player->GetSprite());
		cam->SetOffset(10.f);

		/*mainCamera = new FirstPersonCamera(render);
		FirstPersonCamera* cam = static_cast<FirstPersonCamera*>(mainCamera);
		cam->SetSpeed(5.f);*/

		cam->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		cam->SetSensitivity(0.25f);

		Input::SetCamera(cam);
		player->SetCamera(cam);

		floor = new Sprite(render);
		floor->Init(SPRITE_TYPE::QUAD);
		floor->LoadTexture("../res/Textures/floor.jpg", false);
		floor->material = defaultMaterial;
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(50.f, 50, 1.f);

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i] = new Shape(render);
			cubeLight[i]->Init(SHAPE_TYPE::CUBE);
			cubeLight[i]->material = defaultMaterial;
			cubeLight[i]->SetPos(glm::vec3(15.f, 2.5f, 0.f));
			cubeLight[i]->color.SetColor(0, 255, 0);
		}
		
		spotCubeLight = new Shape(render);
		spotCubeLight->Init(SHAPE_TYPE::CUBE);
		spotCubeLight->material = defaultMaterial;
		spotCubeLight->SetPos(glm::vec3(0.f, 5.f, 0.f));
		spotCubeLight->color.SetColor(255, 0, 0);
		spotCubeLight->SetScale(0.75f);

		tnt = new Sprite(render);
		tnt->Init(SPRITE_TYPE::CUBE);
		tnt->material = defaultMaterial;
		tnt->LoadTexture("../res/Textures/tnt.png", true);
		tnt->SetPos(glm::vec3(10.f, .5f, 10.f));

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
		pointLight->SetPos(player->GetSprite()->GetPos() + glm::vec3(0.f, .5f, 0.f));
		pointLight->color = player->GetSprite()->color;
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
		spotLight->SetLinear(0.07f);
		spotLight->SetQuadratic(0.0075f);
		spotLight->SetCutOff(12.5f);
		spotLight->SetOuterCutOff(17.5f);
	}

	void Game::Update()
	{
		player->Update();
		mainCamera->Update();
		lightManager->GetLasPointLightCreated()->SetPos(player->GetSprite()->GetPos() + glm::vec3(0.f, .5f, 0.f));

		if (Input::IsKeyDown(KEY_ESCAPE))
		{
			CloseEngine();
		}
	}

	void Game::Draw()
	{
		mainCamera->UseCamera();

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i]->Draw();
		}

		floor->Draw();
		spotCubeLight->Draw();
		tnt->Draw();
		player->Draw();
	}

	void Game::DeInit()
	{
		player->DeInit();
		floor->DeInit();
		spotCubeLight->DeInit();
		tnt->DeInit();

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i]->DeInit();
		}
	}
}