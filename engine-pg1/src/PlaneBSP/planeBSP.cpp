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
		quad->SetScale(14.f, 14.f, 1.f);
		quad->color.SetColor(1.f, 1.f, 1.f, 0.1f);
		quad->LookTarget(position + normal);
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