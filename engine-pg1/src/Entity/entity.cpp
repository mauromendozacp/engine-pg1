#include "entity.h"

namespace GL
{
	Entity::Entity()
	{
		this->render = NULL;

		v3Pos = glm::vec3(0.0f);
		v3Rot = glm::vec3(0.0f);
		v3Scale = glm::vec3(1.0f);

		translate = glm::mat4(1.0f);
		rotationX = glm::mat4(1.0f);
		rotationY = glm::mat4(1.0f);
		rotationZ = glm::mat4(1.0f);
		scale = glm::mat4(1.0f);

		model = glm::mat4(1.0f);
		SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		UpdateModel();
	}

	Entity::Entity(Render* render)
	{
		this->render = render;

		SetPos(0.0f, 0.0f, 0.0f);
		SetRotX(0.0f);
		SetRotY(0.0f);
		SetRotZ(0.0f);
		SetScale(1.0f, 1.0f, 1.0f);

		v3Pos = glm::vec3(0.0f);
		v3Rot = glm::vec3(0.0f);
		v3Scale = glm::vec3(1.0f);
		color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		VAO = 0;
		VBO = 0;
		EBO = 0;
	}

	Entity::~Entity()
	{
	}

	void Entity::SetPos(float x, float y, float z)
	{
		v3Pos = glm::vec3(x, y, z);
		translate = glm::translate(glm::mat4(1.0f), v3Pos);
		UpdateModel();
	}

	void Entity::SetRotX(float x) 
	{
		v3Rot[0] = x;
		glm::vec3 axis = glm::vec3(1, 0, 0);
		rotationX = glm::rotate(glm::mat4(1.0f), x, axis);
		UpdateModel();
	}

	void Entity::SetRotY(float y) 
	{
		v3Rot[1] = y;
		glm::vec3 axis = glm::vec3(0, 1, 0);
		rotationY = glm::rotate(glm::mat4(1.0f), y, axis);
		UpdateModel();
	}

	void Entity::SetRotZ(float z) 
	{
		v3Rot[2] = z;
		glm::vec3 axis = glm::vec3(0, 0, 1);
		rotationZ = glm::rotate(glm::mat4(1.0f), z, axis);
		UpdateModel();
	}

	void Entity::SetScale(float x, float y, float z)
	{
		v3Scale = glm::vec3(x, y, z);
		scale = glm::scale(glm::mat4(1.0f), v3Scale);
		UpdateModel();
	}

	void Entity::SetColor(float r, float g, float b, float a)
	{
		this->color = glm::vec4(r, g, b, a);
	}

	glm::mat4 Entity::GetRotation()
	{
		return (rotationX * rotationY * rotationZ);
	}

	void Entity::UpdateModel()
	{
		model = translate * GetRotation() * scale;
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