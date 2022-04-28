#include "entity2D.h"

namespace GL
{
	Entity2D::Entity2D() : Entity()
	{
		color = Color();
		material = nullptr;

		shaderId = 0;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;

		VAO = 0;
		VBO = 0;
		EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
	}

	Entity2D::Entity2D(Render* render) : Entity(render)
	{
		color = Color();
		material = nullptr;

		shaderId = 0;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;

		VAO = 0;
		VBO = 0;
		EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
	}

	Entity2D::~Entity2D()
	{
	}

	void Entity2D::UpdateShader()
	{
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
		render->UpdateColor(uniformColor, uniformAlpha, color.GetColor());
		render->UpdateStatus(uniformAffectedLight, affectedLight);
	}

	void Entity2D::Draw()
	{
		if (material != nullptr)
		{
			material->UpdateShader();
		}

		render->Draw(VAO, VBO, EBO, vertices, tam, vertexs);
	}

	void Entity2D::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);
	}

	void Entity2D::SetCollider(bool hasCollider)
	{
		this->hasCollider = hasCollider;
	}

	void Entity2D::SetMoveable(bool moveable)
	{
		this->moveable = moveable;
	}

	void Entity2D::SetAffectedLight(bool affectedLight)
	{
		this->affectedLight = affectedLight;
	}

	bool Entity2D::IsMoveable()
	{
		return moveable;
	}

	bool Entity2D::HasCollider()
	{
		return hasCollider;
	}

	bool Entity2D::IsAffectedLight()
	{
		return affectedLight;
	}

	void Entity2D::SetUniforms(uint shaderId)
	{
		Entity::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformColor, "color");
		render->SetUniform(shaderId, uniformAlpha, "a");
		render->SetUniform(shaderId, uniformAffectedLight, "affectedLight");
	}
}