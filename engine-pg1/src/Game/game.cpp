#include "game.h"

namespace GameXD
{
	Game::Game()
	{
		camera = nullptr;
		shape = nullptr;
		geometry = nullptr;
	}

	Game::~Game()
	{
		if (camera != nullptr)
		{
			delete camera;
			camera = nullptr;
		}
		if (shape != nullptr)
		{
			delete shape;
			shape = nullptr;
		}
		if (geometry != nullptr)
		{
			delete geometry;
			geometry = nullptr;
		}
	}

	void Game::Init()
	{
		render->SetDepth();

		camera = new Camera(render, input);
		camera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
		camera->SetData(glm::vec3(0.f, 0.f, 25.f), 1.5f, 0.1f);

		shape = new Shape(render);
		shape->Init(SHAPE_TYPE::TRIANGLE);
		shape->SetPos(glm::vec3(0.f));
		shape->SetScale(2.5f);
		shape->SetColor(1.f, 1.f, 1.f, 1.f);

		/*geometry = new Geometry(render);
		geometry->Init(GEOMETRY_TYPE::CUBE);
		geometry->SetPos(glm::vec3(0.f));
		geometry->SetScale(2.5f);
		geometry->SetColor(1.f, 1.f, 1.f, 1.f);*/
	}

	void Game::Update()
	{
		camera->Update(timer->GetDeltaTime());
	}

	void Game::Draw()
	{
		shape->Draw();
		//geometry->Draw();
	}

	void Game::DeInit()
	{
	}
}