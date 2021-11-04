#include "collision.h"

namespace GL
{
	Collision::Collision()
	{

	}

	Collision::~Collision()
	{
	}

	bool Collision::CheckCollision(Entity* entity1, Entity* entity2)
	{
		bool collisionX = entity1->GetPosX() + entity1->GetScaleX() >= entity2->GetPosX() &&
			entity2->GetPosX() + entity2->GetScaleX() >= entity1->GetPosX();
		// collision y-axis?
		bool collisionY = entity1->GetPosY() + entity1->GetScaleY() >= entity2->GetPosY() &&
			entity2->GetPosY() + entity2->GetScaleY() >= entity1->GetPosY();
		// collision only if on both axes
		return collisionX && collisionY;
	}

	void Collision::Overlap(Entity* entity1, Entity* entity2)
	{

	}
}