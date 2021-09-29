#include "entity.h"

namespace GL
{
	Entity::Entity()
	{
		this->render = NULL;

		v3Pos = glm::vec3();
		v3Rot = glm::vec3();
		v3Scale = glm::vec3();

		translate = glm::mat4();
		rotationX = glm::mat4();
		rotationY = glm::mat4();
		rotationZ = glm::mat4();
		scale = glm::mat4();

		trs = glm::mat4();
		color = glm::vec4();

		VAO = 0;
		VBO = 0;
		EBO = 0;
		vertices = 0;
	}

	Entity::Entity(Render* render)
	{
		this->render = render;

		trs = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);
		rotationX = glm::mat4(1.0f);
		rotationY = glm::mat4(1.0f);
		rotationZ = glm::mat4(1.0f);
		scale = glm::mat4(1.0f);

		v3Pos = glm::vec3(0.0f);
		v3Rot = glm::vec3(0.0f);
		v3Scale = glm::vec3(1.0f);
		color = glm::vec4();

		VAO = 0;
		VBO = 0;
		EBO = 0;
		vertices = 0;
	}

	Entity::~Entity()
	{
	}

	void Entity::SetPos(float x, float y, float z)
	{
		v3Pos = glm::vec3(x, y, z);
		translate = glm::translate(glm::mat4(1.0f), v3Pos);
		UpdateTRS();
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

	void Entity::SetScale(float x, float y, float z)
	{
		v3Scale = glm::vec3(x, y, z);
		scale = glm::scale(glm::mat4(1.0f), v3Scale);
		UpdateTRS();
	}

	void Entity::SetColor(glm::vec4 color)
	{
		this->color = color;
	}

	glm::mat4 Entity::GetRotation()
	{
		return (rotationX * rotationY * rotationZ);
	}

	void Entity::UpdateTRS()
	{
		trs = translate * GetRotation() * scale;
	}

	float Entity::GetPosX()
	{
		return v3Pos[0];
	}

	float Entity::GetPosY()
	{
		return v3Pos[1];
	}

	float Entity::GetPosZ()
	{
		return v3Pos[2];
	}

	float Entity::GetRotX()
	{
		return v3Rot[0];
	}

	float Entity::GetRotY()
	{
		return v3Rot[1];
	}

	float Entity::GetRotZ()
	{
		return v3Rot[2];
	}

	float Entity::GetScaleX()
	{
		return v3Scale[0];
	}

	float Entity::GetScaleY()
	{
		return v3Scale[1];
	}

	float Entity::GetScaleZ()
	{
		return v3Scale[2];
	}
}