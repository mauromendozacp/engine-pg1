#include "bsp.h"

namespace GL
{
	Render* BSP::render = nullptr;
	Camera* BSP::camera = nullptr;

	std::list<Entity*> BSP::entities = std::list<Entity*>();
	std::list<PlaneBSP*> BSP::planes = std::list<PlaneBSP*>();

	BSP::BSP()
	{
		render = nullptr;
		camera = nullptr;

		entities = std::list<Entity*>();
		planes = std::list<PlaneBSP*>();
	}

	BSP::~BSP()
	{
	}

	void BSP::Init(Render* rend, Camera* cam)
	{
		render = rend;
		camera = cam;
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

	bool BSP::IsOnBSP(Entity* node)
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

		return drawEntity;
	}
}