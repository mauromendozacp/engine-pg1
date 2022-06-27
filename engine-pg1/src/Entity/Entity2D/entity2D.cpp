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

		this->vertexs = vertexs;
		this->indexes = indexes;

		VAO = 0;
		VBO = 0;
		EBO = 0;

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

		this->vertexs = vertexs;
		this->indexes = indexes;

		VAO = 0;
		VBO = 0;
		EBO = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
		useTexture = false;
	}

	Entity2D::~Entity2D()
	{
	}

	void Entity2D::Draw()
	{
		if (CheckVolume())
		{
			render->Draw(VAO, indexes.size());
		}
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

	void Entity2D::GenerateVolumeAABB()
	{
		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

		for (int i = 0; i < vertexs.size(); i++)
		{
			Vertex vertex = vertexs[i];

			minAABB.x = glm::min(minAABB.x, vertex.Position.x);
			minAABB.y = glm::min(minAABB.y, vertex.Position.y);
			minAABB.z = glm::min(minAABB.z, vertex.Position.z);

			maxAABB.x = glm::max(maxAABB.x, vertex.Position.x);
			maxAABB.y = glm::max(maxAABB.y, vertex.Position.y);
			maxAABB.z = glm::max(maxAABB.z, vertex.Position.z);
		}

		volume = new VolumeAABB(minAABB, maxAABB);
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