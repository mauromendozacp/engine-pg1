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
}