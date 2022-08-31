#include "bsp.h"

namespace GL
{
	BSP::BSP()
	{
		render = nullptr;
		camera = nullptr;

		entities = std::list<Entity*>();
		planes = std::list<PlaneBSP*>();
	}

	BSP::BSP(Render* render, Camera* camera)
	{
		this->render = render;
		this->camera = camera;

		entities = std::list<Entity*>();
		planes = std::list<PlaneBSP*>();
	}

	BSP::~BSP()
	{
	}

	void BSP::Init()
	{
	}

	void BSP::Update()
	{
		for (std::list<Entity*>::iterator itE = entities.begin(); itE != entities.end(); ++itE)
		{
			UpdateNodeVolume((*itE));
		}
	}

	void BSP::Draw()
	{
		for (std::list<PlaneBSP*>::iterator it = planes.begin(); it != planes.end(); ++it)
		{
			(*it)->Draw();
		}
	}

	void BSP::DeInit()
	{
		entities.clear();

		for (std::list<PlaneBSP*>::iterator it = planes.begin(); it != planes.end(); ++it)
		{
			(*it)->DeInit();
		}
		planes.clear();
	}

	void BSP::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void BSP::AddPlane(glm::vec3 position, glm::vec3 normal)
	{
		PlaneBSP* plane = new PlaneBSP();
		plane->Init(render, position, normal);

		planes.push_back(plane);
	}

	void BSP::TogglePlaneStatus()
	{
		for (std::list<PlaneBSP*>::iterator it = planes.begin(); it != planes.end(); ++it)
		{
			(*it)->SwitchCanDrawStatus();
		}
	}

	void BSP::UpdateNodeVolume(Entity* node)
	{
		bool drawEntity = true;

		for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
		{
			if (node->GetGlobalVolume()->IsOnPlane(*(*itP)->plane) != (*itP)->plane->GetSide(camera->GetPos()))
			{
				drawEntity = false;
				break;
			}
		}
		node->visible = drawEntity;

		std::list<Entity*> nodes = node->GetNodes();
		if (!nodes.empty())
		{
			for (std::list<Entity*>::iterator itN = nodes.begin(); itN != nodes.end(); ++itN)
			{
				UpdateNodeVolume((*itN));
			}
		}
	}
}