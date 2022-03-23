#include "collision.h"
#include <math.h>

namespace GL
{
	const float overlapSpeed = 0.35f;

	Collision::Collision()
	{
	}

	Collision::~Collision()
	{
	}

	void Collision::CollisionUpdate(Entity* entity1, Entity* entity2)
	{
		if (CheckCollisionRecRec(entity1, entity2))
		{
			std::cout << "Collision!" << std::endl;

			Overlap(entity1, entity2);
		}
	}

	bool Collision::CheckCollisionRecRec(Entity* entity1, Entity* entity2)
	{
		if (entity2->HasCollider())
		{
			//bool collisionX = entity1->GetPosX() + entity1->GetScaleX() >= entity2->GetPosX() && entity2->GetPosX() + entity2->GetScaleX() >= entity1->GetPosX();
			bool collisionX = entity1->GetPosX() - (entity1->GetScaleX() / 2) + entity1->GetScaleX() >= entity2->GetPosX() - (entity2->GetScaleX() / 2)
				&& entity2->GetPosX() - (entity2->GetScaleX() / 2) + entity2->GetScaleX() >= entity1->GetPosX() - (entity1->GetScaleX() / 2);
			// collision y-axis?
			bool collisionY = entity1->GetPosY() - (entity1->GetScaleY() / 2) + entity1->GetScaleY() >= entity2->GetPosY() - (entity2->GetScaleY() / 2)
				&& entity2->GetPosY() - (entity2->GetScaleY() / 2) + entity2->GetScaleY() >= entity1->GetPosY() - (entity1->GetScaleY() / 2);
			// collision only if on both axes
			return collisionX && collisionY;
		}

		return false;
	}

	void Collision::Overlap(Entity* entity1, Entity* entity2) //Separa ambos objetos en el caso de existir overlap
	{
		if (entity2->IsMoveable())
		{
			do
			{
				glm::vec3 director = glm::normalize(entity2->GetPos() - entity1->GetPos()); //Genero el vector director para saber hacia donde puedo
				entity2->SetPos(entity2->GetPos() + director * overlapSpeed);
			} while (CheckCollisionRecRec(entity1, entity2));
		}
	}
}