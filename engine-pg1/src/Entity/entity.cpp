#include "entity.h"

namespace GL
{
	Entity::Entity(Render* render)
	{
		this->render = render;

		v3Pos = glm::vec3();
		v3Rot = glm::vec3();
		v3Scale = glm::vec3();

		translate = glm::mat4();
		rotationX = glm::mat4();
		rotationY = glm::mat4();
		rotationZ = glm::mat4();
		scale = glm::mat4();

		trs = glm::mat4();
	}

	Entity::~Entity()
	{
		if (render != NULL)
		{
			delete render;
			render = NULL;
		}
	}
}