#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		spotCubeLight = nullptr;
		floor = nullptr;
		tnt = nullptr;

		model = nullptr;
		node = nullptr;
		player = nullptr;

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
		if (floor != nullptr)
		{
			delete floor;
			floor = nullptr;
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

	void Game::InitEntities()
	{
		//model = new Entity3D(render);
		model = ModelImporter::LoadModel(render, "../res/Models/gir/gir.fbx");
		//model = ModelImporter::LoadModel(render, "../res/Models/survival-guitar-backpack/backpack.obj");
		//model = ModelImporter::LoadModel(render, "../res/Models/elshaman/Mauri.obj");
		model->SetPos(glm::vec3(0.f, 2.5f, 0.f));

		//player = static_cast<Player*>(ModelImporter::LoadModel(render, "../res/Models/survival-guitar-backpack/backpack.obj"));
		player = new Player(render);
		player->Init(mainCamera, 5.f, 75.f);
		player->SetCamera(CAMERA_TYPE::TPS);
		player->SetPos(glm::vec3(1.f, 1.5f, 0.f));
		player->SetScale(1.0f);

		floor = new Sprite(render);
		floor->Init(SPRITE_TYPE::QUAD);
		floor->LoadTexture("../res/Textures/floor.jpg", false, TEXTURE_TYPE::BASE);
		floor->material = MaterialManager::GetTextureMaterial();
		floor->color = Color(255, 255, 255);
		floor->SetPos(glm::vec3(0.f, -.5f, 0.f));
		floor->SetRotX(90.f);
		floor->SetScale(50.f, 50.f, 1.f);

		for (int i = 0; i < cubesLenght; i++)
		{
			cubeLight[i] = new Shape(render);
			cubeLight[i]->Init(SHAPE_TYPE::CUBE);
			cubeLight[i]->material = MaterialManager::GetSolidMaterial();
			cubeLight[i]->SetPos(glm::vec3(10.f - 2.5f * i, 2.5f, 10.f));
			cubeLight[i]->color = Color::GetRandomColor();
		}

		spotCubeLight = new Shape(render);
		spotCubeLight->Init(SHAPE_TYPE::CUBE);
		spotCubeLight->material = MaterialManager::GetSolidMaterial();
		spotCubeLight->SetPos(glm::vec3(0.f, 5.f, 0.f));
		spotCubeLight->color.SetColor(255, 0, 0);
		spotCubeLight->SetScale(0.75f);

		tnt = new Sprite(render);
		tnt->Init(SPRITE_TYPE::CUBE);
		tnt->LoadTexture("../res/Textures/tnt.png", true, GL::TEXTURE_TYPE::BASE);
		tnt->material = MaterialManager::GetTextureMaterial();
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
		pointLight->SetPos(player->GetPos() + glm::vec3(0.f, .5f, 0.f));
		pointLight->color = Color(255, 255, 255);
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
		//----------------------------LIGHTS---------------------------------
		if (Input::IsKeyDown(KEY_Z))
		{
			SpotLight* spotLight = lightManager->GetLasSpotLightCreated();
			spotLight->SetEnabled(!spotLight->IsEnabled());
		}
		if (Input::IsKeyDown(KEY_X))
		{
			PointLight* pointLight = lightManager->GetLasPointLightCreated();
			pointLight->SetEnabled(!pointLight->IsEnabled());
		}
		if (Input::IsKeyDown(KEY_C))
		{
			DirectionalLight* directionalLight = lightManager->GetDirectionalLight();
			directionalLight->SetEnabled(!directionalLight->IsEnabled());
		}
		if (Input::IsKeyDown(KEY_V))
		{
			PointLight* pointLight = lightManager->GetLasPointLightCreated();
			pointLight->color = Color::GetRandomColor();
		}

		//----------------------------NODES---------------------------------
		if (Input::IsKeyPressed(KEY_1))
		{
			node = static_cast<Entity3D*>(model);
		}
		if (Input::IsKeyPressed(KEY_2))
		{
			node = static_cast<Entity3D*>(model->GetNode("cabeza"));
		}
		if (Input::IsKeyPressed(KEY_3))
		{
			node = static_cast<Entity3D*>(model->GetNode("hombro_der"));
		}
		if (Input::IsKeyPressed(KEY_4))
		{
			node = static_cast<Entity3D*>(model->GetNode("brazo_der"));
		}
		if (Input::IsKeyPressed(KEY_5))
		{
			node = static_cast<Entity3D*>(model->GetNode("mano_der"));
		}
		if (Input::IsKeyPressed(KEY_6))
		{
			node = static_cast<Entity3D*>(model->GetNode("dedos_der"));
		}
		if (Input::IsKeyPressed(KEY_7))
		{
			node = static_cast<Entity3D*>(model->GetNode("pata_der"));
		}
		if (Input::IsKeyPressed(KEY_8))
		{
			node = static_cast<Entity3D*>(model->GetNode("pata_izq"));
		}
		if (Input::IsKeyPressed(KEY_9))
		{
			node = static_cast<Entity3D*>(model->GetNode("pecho"));
		}
		if (Input::IsKeyPressed(KEY_0))
		{
			node = static_cast<Entity3D*>(model->GetNode("ojos"));
		}

		//----------------------------TRANSFORMS---------------------------------
		if (node != nullptr)
		{
			if (Input::IsKeyPressed(KEY_T))
			{
				node->SetPos(node->GetLocalPosition() - glm::vec3(0.05f, 0.f, 0.f));
			}
			if (Input::IsKeyPressed(KEY_Y))
			{
				node->SetPos(node->GetLocalPosition() + glm::vec3(0.05f, 0.f, 0.f));
			}
			if (Input::IsKeyPressed(KEY_G))
			{
				node->SetRotZ(node->GetLocalRotation().z - 1.f);
			}
			if (Input::IsKeyPressed(KEY_H))
			{
				node->SetRotZ(node->GetLocalRotation().z + 1.f);
			}
			if (Input::IsKeyPressed(KEY_B))
			{
				node->SetScale(node->GetLocalScale() - glm::vec3(0.005f));
			}
			if (Input::IsKeyPressed(KEY_N))
			{
				node->SetScale(node->GetLocalScale() + glm::vec3(0.005f));
			}
			if (Input::IsKeyPressed(KEY_R))
			{
				node->SetPos(glm::vec3(0.f));
				node->SetRot(glm::vec3(0.f));
				node->SetScale(glm::vec3(1.f));
			}
		}

		if (Input::IsKeyDown(KEY_ESCAPE))
		{
			CloseEngine();
		}
	}
}