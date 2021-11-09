#include "collision.h"
#include <math.h>

namespace GL
{
	Collision::Collision()
	{

	}

	Collision::~Collision()
	{

	}

	bool Collision::CheckCollisionRecRec(Entity* entity1, Entity* entity2)
	{
		bool collisionX = entity1->GetPosX() + entity1->GetScaleX() >= entity2->GetPosX() && entity2->GetPosX() + entity2->GetScaleX() >= entity1->GetPosX();
		// collision y-axis?
		bool collisionY = entity1->GetPosY() + entity1->GetScaleY() >= entity2->GetPosY() && entity2->GetPosY() + entity2->GetScaleY() >= entity1->GetPosY();
		// collision only if on both axes
		return collisionX && collisionY;
	}

	void Collision::Overlap(Entity* entity1, Entity* entity2)
	{

		glm::vec3 pos1 = glm::vec3();
		glm::vec3 pos2 = glm::vec3();
		
		glm::vec3 director = glm::vec3();
		director = entity1->GetPivot() - entity2->GetPivot();
		
		while (CheckCollisionRecRec(entity1, entity2))
		{
			
			pos1 = entity1->GetPivot();
			pos2 = entity2->GetPivot();


			if (director.x > 0) //entity1 esta mas a la derecha que entity2
			{
				if (director.y > 0) //entity1 esta mas arriba que entity2
				{
					entity1->SetPos(pos1.x-collisionMover, pos1.y+collisionMover,pos1.z);
					entity2->SetPos(pos2.x+collisionMover, pos2.y-collisionMover,pos2.z);

					std::cout << " 1: Movido hacia arriba y a la izquierda" << std::endl;
					std::cout << " 2: Movido hacia abajo y a la derecha" << std::endl;
				}
				else //entity1 esta mas abajo que entity2
				{
					entity1->SetPos(pos1.x - collisionMover, pos1.y - collisionMover, pos1.z);
					entity2->SetPos(pos2.x + collisionMover, pos2.y + collisionMover, pos2.z);

					std::cout << " 1: Movido hacia abajo y a la izquierda" << std::endl;
					std::cout << " 2: Movido hacia arriba y a la derecha" << std::endl;
				
				}
			}
			else //entity 1 esta mas a la izquierda que entity2
			{
				if (director.y > 0) //entity1 esta mas arriba que entity2
				{
					entity1->SetPos(pos1.x + collisionMover, pos1.y + collisionMover, pos1.z);
					entity2->SetPos(pos2.x - collisionMover, pos2.y - collisionMover, pos2.z);

					std::cout << " 1: Movido hacia arriba y a la derecha" << std::endl;
					std::cout << " 2: Movido hacia abajo y a la izquierda" << std::endl;
				}
				else //entity1 esta mas abajo que entity2
				{
					entity1->SetPos(pos1.x + collisionMover, pos1.y - collisionMover, pos1.z);
					entity2->SetPos(pos2.x - collisionMover, pos2.y + collisionMover, pos2.z);

					std::cout << " 1: Movido hacia abajo y a la derecha" << std::endl;
					std::cout << " 2: Movido hacia arriba y a la izquierda" << std::endl;
				}
			}

			

		};
	}
}