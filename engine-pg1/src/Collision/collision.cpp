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

		//bool collisionX = entity1->GetPosX() + entity1->GetScaleX() >= entity2->GetPosX() && entity2->GetPosX() + entity2->GetScaleX() >= entity1->GetPosX();
		bool collisionX = entity1->GetPosX() + entity1->GetScaleX() >= entity2->GetPosX() && entity2->GetPosX() + entity2->GetScaleX() >= entity1->GetPosX();
		// collision y-axis?
		bool collisionY = entity1->GetPosY() + entity1->GetScaleY() >= entity2->GetPosY() && entity2->GetPosY() + entity2->GetScaleY() >= entity1->GetPosY();
		// collision only if on both axes
		return collisionX && collisionY;
	}

	void Collision::Overlap(Entity* entity1, Entity* entity2) //Separa ambos objetos en el caso de existir overlap
	{

		glm::vec3 pos1 = glm::vec3(); //Tomo las posiciones de ambas entidades
		glm::vec3 pos2 = glm::vec3(); 
		
		glm::vec3 director = glm::vec3(); 

		director = entity1->GetPivot() - entity2->GetPivot(); //Genero el vector director para saber hacia donde puedo 

		do
		{
			director = glm::normalize(entity2->GetPivot() - entity1->GetPivot());
			entity2->SetPos(entity2->GetPivot()+director);
		} while (CheckCollisionRecRec(entity1, entity2));

		/*
		while (CheckCollisionRecRec(entity1, entity2)) //Siempre y cuando haya colisión entre las entidades,
		{
			
			pos1 = entity1->GetPivot(); //Voy a tomar el centro de las entidades. Como son figuras primitivas o regulares
			pos2 = entity2->GetPivot(); //Es lo mismo hacer los cálculos desde el centro como pivot

			if (director.x > 0) //entity1 esta mas a la derecha que entity2
			{
				if (director.y > 0) //entity1 esta mas arriba que entity2
				{
					glm::vec3 point1; //La idea es conseguir 2 puntos para poder hacer un cuadrado
					point1.x = entity1->GetPosX() + entity1->GetScaleX() / 2; //Para ello, obtengo la esquina del la primer entidad
					point1.y = entity1->GetPosY() - entity1->GetScaleY() / 2; //Debe ser la esquina más cercana a la otra entidad, para eso uso director

					glm::vec3 point2;
					point2.x = entity2->GetPosX() - entity2->GetScaleX() / 2; //Y la esquina de la segunda entidad
					point2.y = entity2->GetPosY() + entity2->GetScaleY() / 2; 

					glm::vec3 dir = point2 - point1; //Genero un vector con dichos puntos

					entity1->SetPos(pos1.x - dir.x / 2, pos1.y + dir.y / 2, pos1.z); //Tiro medio vector dir para un lado según corresponda
					entity2->SetPos(pos2.x + dir.x / 2, pos2.y - dir.y / 2, pos2.z); //Tiro el otro medio vector para el lado contrario al anterior

					std::cout << " 1: Movido hacia arriba y a la izquierda" << std::endl;
					std::cout << " 2: Movido hacia abajo y a la derecha" << std::endl;
				}
				else //entity1 esta mas abajo que entity2
				{
					
					glm::vec3 point1;
					point1.x = entity1->GetPosX() + entity1->GetScaleX() / 2;
					point1.y = entity1->GetPosY() + entity1->GetScaleY() / 2;

					glm::vec3 point2;
					point2.x = entity2->GetPosX() - entity2->GetScaleX() / 2;
					point2.y = entity2->GetPosY() - entity2->GetScaleY() / 2;

					glm::vec3 dir = point2 - point1;

					entity1->SetPos(pos1.x - dir.x / 2, pos1.y - dir.y / 2, pos1.z);
					entity2->SetPos(pos2.x + dir.x / 2, pos2.y + dir.y / 2, pos2.z);

					std::cout << " 1: Movido hacia abajo y a la izquierda" << std::endl;
					std::cout << " 2: Movido hacia arriba y a la derecha" << std::endl;

				}
			}
			else //entity 1 esta mas a la izquierda que entity2
			{
				if (director.y > 0) //entity1 esta mas arriba que entity2
				{
					
					glm::vec3 point1;
					point1.x = entity1->GetPosX() - entity1->GetScaleX() / 2;
					point1.y = entity1->GetPosY() - entity1->GetScaleY() / 2;

					glm::vec3 point2;
					point2.x = entity2->GetPosX() + entity2->GetScaleX() / 2;
					point2.y = entity2->GetPosY() + entity2->GetScaleY() / 2;

					glm::vec3 dir = point1 - point2;

					entity1->SetPos(pos1.x + dir.x / 2, pos1.y + dir.y / 2, pos1.z);
					entity2->SetPos(pos2.x - dir.x / 2, pos2.y - dir.y / 2, pos2.z);

					std::cout << " 1: Movido hacia arriba y a la derecha" << std::endl;
					std::cout << " 2: Movido hacia abajo y a la izquierda" << std::endl;
				}
				else //entity1 esta mas abajo que entity2
				{
					
					glm::vec3 point1;
					point1.x = entity1->GetPosX() - entity1->GetScaleX() / 2;
					point1.y = entity1->GetPosY() + entity1->GetScaleY() / 2;

					glm::vec3 point2;
					point2.x = entity2->GetPosX() + entity2->GetScaleX() / 2;
					point2.y = entity2->GetPosY() - entity2->GetScaleY() / 2;

					glm::vec3 dir = point1 - point2;

					entity1->SetPos(pos1.x + dir.x / 2, pos1.y - dir.y / 2, pos1.z);
					entity2->SetPos(pos2.x - dir.x / 2, pos2.y + dir.y / 2, pos2.z);

					std::cout << " 1: Movido hacia abajo y a la derecha" << std::endl;
					std::cout << " 2: Movido hacia arriba y a la izquierda" << std::endl;
				}
			}

			//if (director.x > 0) //entity1 esta mas a la derecha que entity2
			//{
			//	if (director.y > 0) //entity1 esta mas arriba que entity2
			//	{
			//		entity1->SetPos(pos1.x-collisionMover, pos1.y+collisionMover,pos1.z);
			//		entity2->SetPos(pos2.x+collisionMover, pos2.y-collisionMover,pos2.z);

			//		std::cout << " 1: Movido hacia arriba y a la izquierda" << std::endl;
			//		std::cout << " 2: Movido hacia abajo y a la derecha" << std::endl;
			//	}
			//	else //entity1 esta mas abajo que entity2
			//	{
			//		entity1->SetPos(pos1.x - collisionMover, pos1.y - collisionMover, pos1.z);
			//		entity2->SetPos(pos2.x + collisionMover, pos2.y + collisionMover, pos2.z);

			//		std::cout << " 1: Movido hacia abajo y a la izquierda" << std::endl;
			//		std::cout << " 2: Movido hacia arriba y a la derecha" << std::endl;
			//	
			//	}
			//}
			//else //entity 1 esta mas a la izquierda que entity2
			//{
			//	if (director.y > 0) //entity1 esta mas arriba que entity2
			//	{
			//		entity1->SetPos(pos1.x + collisionMover, pos1.y + collisionMover, pos1.z);
			//		entity2->SetPos(pos2.x - collisionMover, pos2.y - collisionMover, pos2.z);

			//		std::cout << " 1: Movido hacia arriba y a la derecha" << std::endl;
			//		std::cout << " 2: Movido hacia abajo y a la izquierda" << std::endl;
			//	}
			//	else //entity1 esta mas abajo que entity2
			//	{
			//		entity1->SetPos(pos1.x + collisionMover, pos1.y - collisionMover, pos1.z);
			//		entity2->SetPos(pos2.x - collisionMover, pos2.y + collisionMover, pos2.z);

			//		std::cout << " 1: Movido hacia abajo y a la derecha" << std::endl;
			//		std::cout << " 2: Movido hacia arriba y a la izquierda" << std::endl;
			//	}
			//}

		};*/
	}
}