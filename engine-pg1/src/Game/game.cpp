#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		player = nullptr;

		objStaticMid = nullptr;
		objStaticLeft = nullptr;
		objStaticFront = nullptr;
		objStaticRight = nullptr;
		objMovable = nullptr;
		node = nullptr;
	}

	Game::~Game()
	{
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}
		if (objStaticMid != nullptr)
		{
			delete objStaticMid;
			objStaticMid = nullptr;
		}
		if (objStaticLeft != nullptr)
		{
			delete objStaticLeft;
			objStaticLeft = nullptr;
		}
		if (objStaticFront != nullptr)
		{
			delete objStaticFront;
			objStaticFront = nullptr;
		}
		if (objStaticRight != nullptr)
		{
			delete objStaticRight;
			objStaticRight = nullptr;
		}
		if (objMovable != nullptr)
		{
			delete objMovable;
			objMovable = nullptr;
		}
		if (node != nullptr)
		{
			delete node;
			node = nullptr;
		}
	}

	void Game::Init()
	{
		render->SetDepth();
		render->clearColor.SetColor(5, 5, 5);

		InitEntities();
		InitLights();
	}

	void Game::Update()
	{
		player->Update();
		mainCamera->Update();
		lightManager->GetLasPointLightCreated()->SetPos(player->GetPos() + glm::vec3(0.f, .5f, 0.f));

		objStaticMid->Update();
		objStaticLeft->Update();
		objStaticFront->Update();
		objStaticRight->Update();
		objMovable->Update();
		
		UpdateInputs();
	}

	void Game::Draw()
	{
		objStaticMid->Draw();
		objStaticLeft->Draw();
		objStaticFront->Draw();
		objStaticRight->Draw();
		objMovable->Draw();

		player->Draw();
	}

	void Game::DeInit()
	{
		player->DeInit();

		objStaticMid->DeInit();
		objStaticLeft->DeInit();
		objStaticFront->DeInit();
		objStaticRight->DeInit();
		objMovable->DeInit();
	}

	void Game::InitEntities()
	{
		//----------------------------PLAYER---------------------------------
		player = new Player(render);
		player->Init(mainCamera, 5.f, 75.f);
		player->SetPos(glm::vec3(0.f, 3.5f, 15.f));

		mainCamera->SetTarget(player);
		mainCamera->SetOffset(10.f);

		//----------------------------OBJECTS---------------------------------
		objStaticMid = new Entity3D(render);
		objStaticMid = ModelImporter::LoadModel(render, "../res/Models/gir/gir.fbx");
		objStaticMid->SetPos(glm::vec3(0.f, 0.f, 0.f));
		objStaticMid->SetScale(0.5f);

		objStaticLeft = new Entity3D(render);
		objStaticLeft = ModelImporter::LoadModel(render, "../res/Models/gir/gir.fbx");
		objStaticLeft->SetPos(glm::vec3(-10.f, 0.f, 0.f));
		objStaticLeft->SetScale(0.5f);

		objStaticFront = new Entity3D(render);
		objStaticFront = ModelImporter::LoadModel(render, "../res/Models/gir/gir.fbx");
		objStaticFront->SetPos(glm::vec3(0.f, 0.f, -10.f));
		objStaticFront->SetScale(0.5f);

		objStaticRight = new Entity3D(render);
		objStaticRight = ModelImporter::LoadModel(render, "../res/Models/gir/gir.fbx");
		objStaticRight->SetPos(glm::vec3(10.f, 0.f, 0.f));
		objStaticRight->SetScale(0.5f);

		objMovable = new Entity3D(render);
		objMovable = ModelImporter::LoadModel(render, "../res/Models/gir/gir.fbx");
		objMovable->SetPos(glm::vec3(5.f, 0.f, 0.f));
		objMovable->SetScale(0.75f);

		//------------------------------BSP---------------------------------
		BSP::AddPlane(glm::vec3(-7.f, 0.f, 5.f), glm::vec3(1.f, 0.f, 0.f));
		BSP::AddPlane(glm::vec3(0.f, 0.f, -2.5f), glm::vec3(0.f, 0.f, 1.f));
		BSP::AddPlane(glm::vec3(7.f, 0.f, 5.f), glm::vec3(-1.f, 0.f, 0.f));
		
		BSP::AddEntity(objStaticMid);
		BSP::AddEntity(objStaticLeft);
		BSP::AddEntity(objStaticFront);
		BSP::AddEntity(objStaticRight);
		BSP::AddEntity(objMovable);
	}

	void Game::InitLights()
	{
		lightManager->AddLight(LIGHT_TYPE::DIRECTIONAL);
		DirectionalLight* directionalLight = lightManager->GetDirectionalLight();
		directionalLight->color.SetColor(255, 255, 255);
		directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
		directionalLight->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		directionalLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		directionalLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

		lightManager->AddLight(LIGHT_TYPE::POINTLIGHT);
		PointLight* pointLight = lightManager->GetLasPointLightCreated();
		pointLight->SetPos(glm::vec3(0.f, 0.f, 2.5f));
		pointLight->color = Color(255, 255, 255);
		pointLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
		pointLight->SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
		pointLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		pointLight->SetConstant(1.f);
		pointLight->SetLinear(0.09f);
		pointLight->SetQuadratic(0.032f);
	}

	void Game::UpdateInputs()
	{
		//----------------------------LIGHTS---------------------------------
		if (Input::IsKeyDown(KEY_Z))
		{
			PointLight* pointLight = lightManager->GetLasPointLightCreated();
			pointLight->color = Color::GetRandomColor();
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

		//----------------------------NODES---------------------------------
		if (Input::IsKeyDown(KEY_1))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("RootNode")->GetNode(0));
		}
		if (Input::IsKeyDown(KEY_2))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("cabeza"));
		}
		if (Input::IsKeyDown(KEY_3))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("hombro_der"));
		}
		if (Input::IsKeyDown(KEY_4))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("brazo_der"));
		}
		if (Input::IsKeyDown(KEY_5))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("mano_der"));
		}
		if (Input::IsKeyDown(KEY_6))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("dedo1"));
		}
		if (Input::IsKeyDown(KEY_7))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("ojos"));
		}
		if (Input::IsKeyDown(KEY_8))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("patas"));
		}
		if (Input::IsKeyDown(KEY_9))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("pata_izq"));
		}
		if (Input::IsKeyDown(KEY_0))
		{
			node = static_cast<Entity3D*>(objMovable->GetNode("cuerpo"));
		}

		//----------------------------TRANSFORMS---------------------------------
		if (node != nullptr)
		{
			if (Input::IsKeyPressed(KEY_G))
			{
				node->SetPos(node->GetLocalPosition() - glm::vec3(0.05f, 0.f, 0.f));
			}
			if (Input::IsKeyPressed(KEY_J))
			{
				node->SetPos(node->GetLocalPosition() + glm::vec3(0.05f, 0.f, 0.f));
			}
			if (Input::IsKeyPressed(KEY_H))
			{
				node->SetPos(node->GetLocalPosition() - glm::vec3(0.f, 0.05f, 0.f));
			}
			if (Input::IsKeyPressed(KEY_Y))
			{
				node->SetPos(node->GetLocalPosition() + glm::vec3(0.f, 0.05f, 0.f));
			}
			if (Input::IsKeyPressed(KEY_T))
			{
				node->SetRotZ(node->GetLocalRotation().z - 1.f);
			}
			if (Input::IsKeyPressed(KEY_U))
			{
				node->SetRotZ(node->GetLocalRotation().z + 1.f);
			}
			if (Input::IsKeyPressed(KEY_B))
			{
				node->SetScale(node->GetLocalScale() - glm::vec3(0.005f));
			}
			if (Input::IsKeyPressed(KEY_M))
			{
				node->SetScale(node->GetLocalScale() + glm::vec3(0.005f));
			}
			if (Input::IsKeyDown(KEY_N))
			{
				node->ToggleDrawVolume();
			}
		}
		if (Input::IsKeyDown(KEY_R))
		{
			objMovable->Reset();
		}

		if (Input::IsKeyDown(KEY_F))
		{
			BSP::TogglePlaneStatus();
		}

		if (Input::IsKeyDown(KEY_V))
		{
			BSP::ToggleStatus();
		}

		if (Input::IsKeyDown(KEY_ESCAPE))
		{
			CloseEngine();
		}
	}
}