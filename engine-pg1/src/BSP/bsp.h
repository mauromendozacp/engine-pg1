#ifndef BSP_H
#define BSP_H

#include "exports.h"

#include "Entity/entity.h"
#include <PlaneBSP/planeBSP.h>
#include <Camera/camera.h>

#include <list>

namespace GL
{
	class GRAPHICSENGINE_API BSP
	{
	public:
		BSP();
		BSP(Render* render, Camera* camera);
		~BSP();

		void Init();
		void Update();
		void Draw();
		void DeInit();

		void AddEntity(Entity* entity);
		void AddPlane(glm::vec3 position, glm::vec3 normal);
		void TogglePlaneStatus();

	private:
		Render* render;
		Camera* camera;

		std::list<Entity*> entities;
		std::list<PlaneBSP*> planes;
	};
}

#endif // !BSP_H