#ifndef COLLISION_H
#define COLLISION_H

#include "exports.h"
#include "Entity/entity.h"

namespace GL
{
	class GRAPHICSENGINE_API Collision
	{
	public:
		Collision();
		~Collision();

		static bool CheckCollision(Entity* entity1, Entity* entity2);
		static void Overlap(Entity* entity1, Entity* entity2);

	private:
		
	};
}

#endif // !COLLISION_H