#ifndef COLLISION_H
#define COLLISION_H

#include "exports.h"

#include "Entity/Entity2D/entity2d.h"

namespace GL
{
	const float collisionMoveSpeed = 0.001f;

	class GRAPHICSENGINE_API Collision2D
	{
	public:
		Collision2D();
		~Collision2D();

		static void CollisionUpdate(Entity2D* entity1, Entity2D* entity2);
		static bool CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2);
		static void Overlap(Entity2D* entity1, Entity2D* entity2);
	};
}

#endif // !COLLISION_H