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

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();

		VAO = 0;
		VBO = 0;
		EBO = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
		useTexture = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = -glm::vec3(std::numeric_limits<float>::max());
	}

	Entity2D::Entity2D(Render* render) : Entity(render)
	{
		color = Color();
		material = nullptr;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();

		VAO = 0;
		VBO = 0;
		EBO = 0;

		hasCollider = false;
		moveable = false;

		affectedLight = true;
		useTexture = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = -glm::vec3(std::numeric_limits<float>::max());
	}

	Entity2D::~Entity2D()
	{
	}

	void Entity2D::Draw()
	{
		if (IsCanDraw())
		{
			render->Draw(VAO, indexes.size());
		}
	}

	void Entity2D::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);

		vertexs.clear();
		indexes.clear();

		localVolume->DeInit();
		globalVolume->DeInit();
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

		localVolume = new VolumeAABB(minAABB, maxAABB);
		globalVolume = new VolumeAABB();
		globalVolume->SetGlobalVolume(localVolume, matrix.model);
		globalVolume->Init(render);

		if (parent != nullptr)
		{
			Entity2D* parent2d = static_cast<Entity2D*>(parent);
			parent2d->minAABB = glm::min(minAABB, parent2d->minAABB);
			parent2d->maxAABB = glm::max(minAABB, parent2d->minAABB);
		}
	}
}