#include "planeBSP.h"

namespace GL
{
	PlaneBSP::PlaneBSP()
	{
		plane = nullptr;
		quad = nullptr;

		canDraw = false;
	}

	PlaneBSP::~PlaneBSP()
	{
		if (plane != nullptr)
		{
			delete plane;
			plane = nullptr;
		}
		if (quad != nullptr)
		{
			delete quad;
			quad = nullptr;
		}
	}

	void PlaneBSP::Init(Render* render, glm::vec3 position, glm::vec3 normal)
	{
		plane = new Plane(normal, position);

		quad = new Shape(render);
		quad->Init(SHAPE_TYPE::QUAD);
		quad->material = MaterialManager::GetSolidMaterial();
		quad->SetPos(position);

		if (glm::abs(normal.x) > 0.f)
		{
			quad->SetRotY(90.f);
		}
		//quad->LookTarget(position + normal);
	}

	void PlaneBSP::Draw()
	{
		if (canDraw && quad != nullptr)
		{
			quad->Draw();
		}
	}

	void PlaneBSP::DeInit()
	{
		if (quad != nullptr)
		{
			quad->DeInit();
		}
	}

	void PlaneBSP::SwitchCanDrawStatus()
	{
		canDraw = !canDraw;
	}

	bool PlaneBSP::SamePositionsSide(glm::vec3 point1, glm::vec3 point2)
	{
		return plane->SameSide(point1, point2);
	}
}