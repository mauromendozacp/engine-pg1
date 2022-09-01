#include "bsp.h"

namespace GL
{
	bool BSP::enabled = true;
	Render* BSP::render = nullptr;
	Camera* BSP::camera = nullptr;

	std::list<Entity*> BSP::entities = std::list<Entity*>();
	std::list<PlaneBSP*> BSP::planes = std::list<PlaneBSP*>();

	BSP::BSP()
	{
		enabled = true;
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

	bool BSP::IsOnPlanesBSP(Entity* node)
	{
		if (!enabled) return true;

		for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
		{
			if (node->GetGlobalVolume()->IsOnPlane(*(*itP)->plane) != (*itP)->plane->GetSide(camera->GetPos()))
			{
				return false;
			}
		}

		return true;
	}

	void BSP::TogglePlaneStatus()
	{
		for (std::list<PlaneBSP*>::iterator it = planes.begin(); it != planes.end(); ++it)
		{
			(*it)->SwitchCanDrawStatus();
		}
	}

	void BSP::ToggleStatus()
	{
		enabled = !enabled;
	}
}