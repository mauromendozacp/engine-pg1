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
	void Entity::UpdateTRS()
	{
		trs = translate * Rotation() * scale;
	}
	void Entity::SetTranslate(float x, float y, float z)
	{
		v3Pos = glm::vec3(x, y, z);
		scale = glm::scale(glm::mat4(1.0f), v3Pos);
	}
	void Entity::SetRotX(float x) 
	{
		v3Rot[0] = x;
		glm::vec3 axis = glm::vec3(1, 0, 0);
		rotationX = glm::rotate(glm::mat4(1.0f), x, axis);
		UpdateTRS();
	}
	void Entity::SetRotY(float y) 
	{
		v3Rot[1] = y;
		glm::vec3 axis = glm::vec3(0, 1, 0);
		rotationY = glm::rotate(glm::mat4(1.0f), y, axis);
		UpdateTRS();
	}
	void Entity::SetRotZ(float z) 
	{
		v3Rot[2] = z;
		glm::vec3 axis = glm::vec3(0, 0, 1);
		rotationZ = glm::rotate(glm::mat4(1.0f), z, axis);
		UpdateTRS();
	}
	glm::mat4 Entity::Rotation()
	{
		return (rotationX * rotationY * rotationZ);
	}
	void Entity::SetScale(float x, float y, float z)
	{
		v3Scale = glm::vec3(x, y, z);
		scale = glm::scale(glm::mat4(1.0f), v3Scale);
	}
	void Entity::SetColor(glm::vec4 color)
	{
		this->color = color;
	}
}