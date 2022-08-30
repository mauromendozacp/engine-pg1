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
			bool drawEntity = true;
			for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
			{
				if ((*itP)->SamePositionsSide((*itE)->GetPos(), camera->GetPos()))
				{
					drawEntity = false;
					break;
				}
			}

			(*itE)->visible = drawEntity;
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
}