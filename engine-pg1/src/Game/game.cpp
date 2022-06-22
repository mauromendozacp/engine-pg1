#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		spotCubeLight = nullptr;
		floor = nullptr;
		tnt = nullptr;

		model = nullptr;
		character = nullptr;
		player = nullptr;

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
		if (model != nullptr)
		{
			delete model;
			model = nullptr;
		}
		if (character != nullptr)
		{
			delete character;
			character = nullptr;
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
		lightManager->GetLasPointLightCreated()->SetPos(player->GetPos() + glm::vec3(0.f, .5f, 0.f));
		
		UpdateInputs();
	}

	void Game::Draw()
	{
		mainCamera->UseCamera();

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i]->Draw();
		}

		spotCubeLight->Draw();
		floor->Draw();
		tnt->Draw();
		model->Draw();

		player->Draw();
	}

	void Game::DeInit()
	{
		player->DeInit();
		floor->DeInit();
		spotCubeLight->DeInit();
		tnt->DeInit();
		model->DeInit();

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i]->DeInit();
		}
	}

	void Game::InitMaterial()
	{
		defaultSolidMaterial = new SolidMaterial(render);
		defaultSolidMaterial->Init();
		defaultSolidMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultSolidMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		defaultSolidMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultSolidMaterial->SetShininess(64.f);

		defaultTextureMaterial = new TextureMaterial(render);
		defaultTextureMaterial->Init();
		defaultTextureMaterial->SetDiffuse(0);
		defaultTextureMaterial->SetSpecular(1);
		defaultTextureMaterial->SetShininess(64.f);
	}

	void Game::InitEntities()
	{
		model = new Entity3D(render);
		model = ModelImporter::LoadModel(render, "../res/Models/elshaman/Mauri.obj");
		model->SetPos(glm::vec3(0.f, -.5f, -15.f));
		model->SetScale(0.05f);
		model->material = defaultTextureMaterial;

		//player = static_cast<Player*>(ModelImporter::LoadModel(render, "../res/Models/survival-guitar-backpack/backpack.obj"));
		player = new Player(render);
		player->Init(mainCamera, 5.f, 75.f);
		player->material = defaultTextureMaterial;
		player->color = Color(255, 255, 255);
		player->SetScale(1.0f);
		player->SetCamera(CAMERA_TYPE::TPS);

		floor = new Sprite(render);
		floor->Init(SPRITE_TYPE::QUAD);
		floor->LoadTexture("../res/Textures/floor.jpg", false, TEXTURE_TYPE::BASE);
		floor->material = defaultTextureMaterial;
		floor->color = Color(255, 255, 255);
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

		occlusionCulling->AddEntity(tnt);
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
		pointLight->SetPos(player->GetPos() + glm::vec3(0.f, .5f, 0.f));
		pointLight->color = player->color;
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
			glm::vec3 guitarScale = model->GetScale();
			guitarScale += glm::vec3(1) * Timer::GetDeltaTime();
			model->SetScale(guitarScale);
		}
		if (Input::IsKeyPressed(KEY_6))
		{
			glm::vec3 guitarScale = model->GetScale();
			guitarScale -= glm::vec3(1) * Timer::GetDeltaTime();
			model->SetScale(guitarScale);
		}
		if (Input::IsKeyPressed(KEY_7))
		{
			float guitarRotX = model->GetRotX();
			guitarRotX -= 15.f * Timer::GetDeltaTime();
			model->SetRotX(guitarRotX);
		}
		if (Input::IsKeyPressed(KEY_8))
		{
			float guitarRotX = model->GetRotX();
			guitarRotX += 15.f * Timer::GetDeltaTime();
			model->SetRotX(guitarRotX);
		}
		if (Input::IsKeyPressed(KEY_9))
		{
			Entity* guitarNode1 = model->GetNode("Cylinder.030__0");
			guitarNode1->SetPos(guitarNode1->GetLocalPosition() - glm::vec3(0.5f, 0.f, 0.f));
		}
		if (Input::IsKeyPressed(KEY_0))
		{
			Entity* guitarNode1 = model->GetNode("Cylinder.030__0");
			guitarNode1->SetPos(guitarNode1->GetLocalPosition() + glm::vec3(0.5f, 0.f, 0.f));
		}

		if (Input::IsKeyDown(KEY_ESCAPE))
		{
			CloseEngine();
		}
	}
}