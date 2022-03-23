#include "entity2D.h"

namespace GL
{
	Entity2D::Entity2D() : Entity()
	{
		color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		VAO = 0;
		VBO = 0;
		EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		hasCollider = false;
		moveable = false;
	}

	Entity2D::Entity2D(Render* render) : Entity(render)
	{
		color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		VAO = 0;
		VBO = 0;
		EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		hasCollider = false;
		moveable = false;
	}

	Entity2D::~Entity2D()
	{
	}

	void Entity2D::SetColor(glm::vec4 color)
	{
		this->color = color;
	}

	void Entity2D::SetColor(float r, float g, float b, float a)
	{
		SetColor({ r, g, b, a });
	}

	glm::vec4 Entity2D::GetColor()
	{
		return color;
	}

	void Entity2D::SetCollider(bool col)
	{
		hasCollider = col;
	}

	void Entity2D::SetMoveable(bool mov)
	{
		moveable = mov;
	}

	bool Entity2D::IsMoveable()
	{
		return moveable;
	}

	bool Entity2D::HasCollider()
	{
		return hasCollider;
	}

	void Entity2D::Draw(unsigned int shaderId)
	{
		render->Draw(matrix.model, VAO, VBO, EBO, vertices, tam, vertexs, shaderId);
	}

	void Entity2D::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);
	}

	void Entity2D::SetUniforms(uint shaderId)
	{
		Entity::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformColor, "color");
		render->SetUniform(shaderId, uniformAlpha, "a");
	}
}