#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		guitarBackpack1 = nullptr;
		guitarBackpack2 = nullptr;
		spotCubeLight = nullptr;
		player = nullptr;
		floor = nullptr;
		tnt = nullptr;

		defaultSolidMaterial = nullptr;
		defaultTextureMaterial = nullptr;

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i] = nullptr;
		}
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
		if (defaultSolidMaterial != nullptr)
		{
			delete defaultSolidMaterial;
			defaultSolidMaterial = nullptr;
		}
		if (defaultTextureMaterial != nullptr)
		{
			delete defaultTextureMaterial;
			defaultTextureMaterial = nullptr;
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
		if (guitarBackpack1 != nullptr)
		{
			delete guitarBackpack1;
			guitarBackpack1 = nullptr;
		}
		if (guitarBackpack2 != nullptr)
		{
			delete guitarBackpack2;
			guitarBackpack2 = nullptr;
		}

		for (int i = 0; i < cubesLenght; i++)
		{
			if (cubeLight[i] != nullptr)
			{
				delete cubeLight[i];
				cubeLight[i] = nullptr;
			}
		}
	}

	void Game::Init()
	{
		render->SetDepth();

		InitMaterial();
		InitEntities();
		InitLights();
	}

	void Game::Update()
	{
		player->Update();
		mainCamera->Update();
		lightManager->GetLasPointLightCreated()->SetPos(player->GetSprite()->GetPos() + glm::vec3(0.f, .5f, 0.f));
		
		UpdateInputs();
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
		guitarBackpack1->Draw();
		guitarBackpack2->Draw();

		player->Draw();
	}

	void Game::DeInit()
	{
		player->DeInit();
		floor->DeInit();
		spotCubeLight->DeInit();
		tnt->DeInit();
		guitarBackpack1->DeInit();
		guitarBackpack2->DeInit();

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i]->DeInit();
		}
	}

	void Game::InitMaterial()
	{
		defaultSolidMaterial = new SolidMaterial(render);
		defaultSolidMaterial->Init(render->GetSolidShaderId());
		defaultSolidMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultSolidMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		defaultSolidMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultSolidMaterial->SetShininess(64.f);

		defaultTextureMaterial = new TextureMaterial(render);
		defaultTextureMaterial->Init(render->GetTextureShaderId());
		defaultTextureMaterial->SetDiffuse(0);
		defaultTextureMaterial->SetSpecular(1);
		defaultTextureMaterial->SetShininess(64.f);
	}

	void Game::InitEntities()
	{
		guitarBackpack1 = new Entity3D(render);
		guitarBackpack1->Init("../res/Models/survival-guitar-backpack/backpack.obj");
		guitarBackpack1->SetPos(glm::vec3(-5.f, 1.0f, -15.f));
		guitarBackpack1->SetScale(1.0f);
		guitarBackpack1->material = defaultTextureMaterial;

		guitarBackpack2 = new Entity3D(render);
		guitarBackpack2->Init("../res/Models/survival-guitar-backpack/backpack.obj");
		guitarBackpack2->SetPos(glm::vec3(5.f, 1.0f, -15.f));
		guitarBackpack2->SetScale(1.0f);
		guitarBackpack2->material = defaultTextureMaterial;

		player = new Player(mainCamera);
		player->Init(render, defaultTextureMaterial, 5.f, 75.f, "../res/Textures/player.png");
		player->SetCamera(render, window, CAMERA_TYPE::TPS);
		mainCamera = player->GetCamera();

		floor = new Sprite(render);
		floor->Init(SPRITE_TYPE::QUAD);
		floor->LoadTexture("../res/Textures/floor.jpg", false, TEXTURE_TYPE::BASE);
		floor->material = defaultTextureMaterial;
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(50.f, 50.f, 1.f);

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i] = new Shape(render);
			cubeLight[i]->Init(SHAPE_TYPE::CUBE);
			cubeLight[i]->material = defaultSolidMaterial;
			cubeLight[i]->SetPos(glm::vec3(10.f - 2.5f * i, 2.5f, 10.f));
			cubeLight[i]->color = Color::GetRandomColor();
		}

		spotCubeLight = new Shape(render);
		spotCubeLight->Init(SHAPE_TYPE::CUBE);
		spotCubeLight->material = defaultSolidMaterial;
		spotCubeLight->SetPos(glm::vec3(0.f, 5.f, 0.f));
		spotCubeLight->color.SetColor(255, 0, 0);
		spotCubeLight->SetScale(0.75f);

		tnt = new Sprite(render);
		tnt->Init(SPRITE_TYPE::CUBE);
		tnt->material = defaultTextureMaterial;
		tnt->LoadTexture("../res/Textures/tnt.png", true, GL::TEXTURE_TYPE::BASE);
		tnt->SetPos(glm::vec3(2.5f, 0.f, 2.5f));
	}

	void Game::InitLights()
	{
		lightManager->AddLight(LIGHT_TYPE::DIRECTIONAL);
		DirectionalLight* directionalLight = lightManager->GetDirectionalLight();
		directionalLight->color.SetColor(105, 105, 105);
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

	void Game::UpdateInputs()
	{
		if (Input::IsKeyDown(KEY_1))
		{
			SpotLight* spotLight = lightManager->GetLasSpotLightCreated();
			spotLight->SetEnabled(!spotLight->IsEnabled());
		}
		if (Input::IsKeyDown(KEY_2))
		{
			PointLight* pointLight = lightManager->GetLasPointLightCreated();
			pointLight->SetEnabled(!pointLight->IsEnabled());
		}
		if (Input::IsKeyDown(KEY_3))
		{
			DirectionalLight* directionalLight = lightManager->GetDirectionalLight();
			directionalLight->SetEnabled(!directionalLight->IsEnabled());
		}
		if (Input::IsKeyDown(KEY_4))
		{
			PointLight* pointLight = lightManager->GetLasPointLightCreated();
			pointLight->color = Color::GetRandomColor();
		}
		if (Input::IsKeyPressed(KEY_5))
		{
			glm::vec3 guitarScale = guitarBackpack1->GetScale();
			guitarScale += glm::vec3(1) * Timer::GetDeltaTime();
			guitarBackpack1->SetScale(guitarScale);
		}
		if (Input::IsKeyPressed(KEY_6))
		{
			glm::vec3 guitarScale = guitarBackpack1->GetScale();
			guitarScale -= glm::vec3(1) * Timer::GetDeltaTime();
			guitarBackpack1->SetScale(guitarScale);
		}
		if (Input::IsKeyPressed(KEY_7))
		{
			float guitarRotX = guitarBackpack1->GetRotX();
			guitarRotX -= 15.f * Timer::GetDeltaTime();
			guitarBackpack1->SetRotX(guitarRotX);
		}
		if (Input::IsKeyPressed(KEY_8))
		{
			float guitarRotX = guitarBackpack1->GetRotX();
			guitarRotX += 15.f * Timer::GetDeltaTime();
			guitarBackpack1->SetRotX(guitarRotX);
		}
		if (Input::IsKeyPressed(KEY_9))
		{
			glm::vec3 guitarPos = guitarBackpack1->GetPos();
			guitarPos -= glm::vec3(1) * Timer::GetDeltaTime();
			guitarBackpack1->SetPos(guitarPos);
		}
		if (Input::IsKeyPressed(KEY_0))
		{
			glm::vec3 guitarPos = guitarBackpack1->GetPos();
			guitarPos += glm::vec3(1) * Timer::GetDeltaTime();
			guitarBackpack1->SetPos(guitarPos);
		}

		if (Input::IsKeyDown(KEY_ESCAPE))
		{
			CloseEngine();
		}
	}
}