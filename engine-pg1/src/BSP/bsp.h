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
		~BSP();

		static void Init(Render* rend, Camera* cam);
		static void Update();
		static void Draw();
		static void DeInit();

		static void AddEntity(Entity* entity);

		static void FindPlanes(Entity* scene);
		static void AddPlane(Entity* node);

		static void UpdateNodeVolume(Entity* node);
		static void UpdatePlanes();

		static void TogglePlaneStatus();
		static void ToggleStatus();

	private:
		static bool enabled;
		static Render* render;
		static Camera* camera;

		static std::list<Entity*> entities;
		static std::list<PlaneBSP*> planes;
	};
}

#endif // !BSP_H