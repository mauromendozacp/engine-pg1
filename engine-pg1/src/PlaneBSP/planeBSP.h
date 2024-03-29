#ifndef PLANE_BSP_H
#define PLANE_BSP_H

#include "exports.h"
#include "Plane/plane.h"
#include "Entity/Entity2D/Shape/shape.h"
#include "Material/MaterialManager/materialManager.h"

namespace GL
{
	class GRAPHICSENGINE_API PlaneBSP
	{
	public:
		PlaneBSP();
		~PlaneBSP();

		void Init(Render* render, glm::vec3 position, glm::vec3 normal);
		void Draw();
		void DeInit();

		void SwitchCanDrawStatus();
		bool SamePositionsSide(glm::vec3 point1, glm::vec3 point2);

		Plane* plane;
		Shape* quad;

	private:
		bool canDraw;
	};
}

#endif // !PLANE_BSP_H