#ifndef COLLISION_H
#define COLLISION_H

#include "exports.h"
#include "Entity2D/entity2d.h"

namespace GL
{

	const float collisionMover = 0.001f;

	class GRAPHICSENGINE_API Collision
	{
	public:
		Collision();
		~Collision();

		static void CollisionUpdate(Entity2D* entity1, Entity2D* entity2);
		static bool CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2);
		static void Overlap(Entity2D* entity1, Entity2D* entity2);

	private:
		
	};
}

#endif // !COLLISION_H