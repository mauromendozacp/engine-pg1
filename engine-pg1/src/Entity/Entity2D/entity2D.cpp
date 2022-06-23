#include "entity2D.h"

namespace GL
{
	Entity2D::Entity2D() : Entity()
	{
		color = Color();
		material = nullptr;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;

		tam = 0;
		indices = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
		useTexture = false;
	}

	Entity2D::Entity2D(Render* render) : Entity(render)
	{
		color = Color();
		material = nullptr;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;

		tam = 0;
		indices = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
		useTexture = false;
	}

	Entity2D::~Entity2D()
	{
	}

	void Entity2D::UpdateShader()
	{
		Entity::UpdateShader();
		render->UpdateColor(uniformColor, uniformAlpha, color.GetColor());
		render->UpdateStatus(uniformAffectedLight, affectedLight);
		render->UpdateStatus(uniformUseTexture, useTexture);

		if (material != nullptr)
		{
			material->UpdateShader();
		}
	}

	void Entity2D::Draw()
	{
		if (canDraw)
		{
			render->Draw(VAO, indices);
		}
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

	void Entity2D::SetUniforms()
	{
		Entity::SetUniforms();
		render->SetUniform(uniformColor, "color");
		render->SetUniform(uniformAlpha, "a");
		render->SetUniform(uniformAffectedLight, "affectedLight");
		render->SetUniform(uniformUseTexture, "useTexture");
	}
}