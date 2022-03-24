#include "entity2D.h"

namespace GL
{
	const float colorValue = 255.f;

	Entity2D::Entity2D() : Entity()
	{
		color = glm::vec4(1.f);

		uniformColor = 0;
		uniformAlpha = 0;
		uniformUseTexture = 0;
		uniformAffectedLight = 0;

		VAO = 0;
		VBO = 0;
		EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		hasCollider = false;
		moveable = false;

		useTexture = false;
		affectedLight = true;
	}

	Entity2D::Entity2D(Render* render) : Entity(render)
	{
		color = glm::vec4(1.f);

		uniformColor = 0;
		uniformAlpha = 0;
		uniformUseTexture = 0;
		uniformAffectedLight = 0;

		VAO = 0;
		VBO = 0;
		EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		hasCollider = false;
		moveable = false;

		useTexture = false;
		affectedLight = true;
	}

	Entity2D::~Entity2D()
	{
	}

	void Entity2D::UpdateShader()
	{
		render->UseShader();
		render->UpdateMVP(matrix.model, uniformModel, uniformView, uniformProjection);
		render->UpdateColor(color, uniformColor, uniformAlpha);
		render->UpdateStatus(affectedLight, uniformAffectedLight);
		render->UpdateUseTexture(useTexture, uniformUseTexture);
	}

	void Entity2D::Draw()
	{
		render->Draw(VAO, VBO, EBO, vertices, tam, vertexs);
	}

	void Entity2D::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);
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
		render->SetUniform(uniformUseTexture, "useTexture");
		render->SetUniform(uniformAffectedLight, "affectedLight");
	}

	void Entity2D::SetColorRGB(float r, float g, float b, float a)
	{
		this->color = glm::vec4(r / color.r, g / color.g, b / color.b, a);
	}
}