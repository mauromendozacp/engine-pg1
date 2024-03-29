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

	void BSP::Update()
	{
		if (!enabled) return;

		UpdatePlanes();

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

	void BSP::FindPlanes(Entity* scene)
	{
		std::list<Entity*> nodes = scene->GetNodes();
		if (!nodes.empty())
		{
			for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
			{
				Entity* node = (*it);
				if (node->name.find("bsp") != std::string::npos)
				{
					AddPlane(node);
				}

				FindPlanes(node);
			}
		}
	}

	void BSP::AddPlane(Entity* node)
	{
		PlaneBSP* plane = new PlaneBSP();
		plane->Init(render, node->GetPos(), node->transform.forward);

		planes.push_back(plane);
	}

	void BSP::UpdateNodeVolume(Entity* node)
	{
		if (node->isOnFrustum)
		{
			bool drawEntity = true;

			for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
			{
				Plane* plane = (*itP)->plane;
				if (node->GetGlobalVolume()->IsOnPlane(*plane) != plane->GetSide(camera->GetPos()))
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

	void BSP::UpdatePlanes()
	{
		for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
		{
			Plane* plane = (*itP)->plane;
			if (!plane->GetSide(camera->GetPos()))
			{
				plane->Flip();
			}
		}
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