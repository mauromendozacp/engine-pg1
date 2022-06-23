#include "entity.h"

namespace GL
{
	const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;

	Entity::Entity()
	{
		render = nullptr;

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();

		VAO = 0;
		VBO = 0;
		EBO = 0;

		name = "";

		parent = nullptr;
		nodes = std::list<Entity*>();

		transform.position = glm::vec3(0.f);
		transform.eulerAngles = glm::vec3(0.f);
		transform.scale = glm::vec3(1.f);
		transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.localPosition = glm::vec3(0.f);
		transform.localEulerAngles = glm::vec3(0.f);
		transform.localScale = glm::vec3(1.f);
		transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.forward = glm::vec3(0.f, 0.f, 1.f);
		transform.up = glm::vec3(0.f, 1.f, 0.f);
		transform.right = glm::vec3(1.f, 0.f, 0.f);

		matrix.model = glm::mat4(1.f);
		matrix.translate = glm::mat4(1.f);
		matrix.rotationX = glm::mat4(1.f);
		matrix.rotationY = glm::mat4(1.f);
		matrix.rotationZ = glm::mat4(1.f);
		matrix.scale = glm::mat4(1.f);

		uniformModel = 0;
		uniformView = 0;
		uniformProjection = 0;

		UpdateTransform();
		UpdateMatrix();
	}

	Entity::Entity(Render* render)
	{
		this->render = render;

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();

		VAO = 0;
		VBO = 0;
		EBO = 0;

		name = "";

		parent = nullptr;
		nodes = std::list<Entity*>();

		transform.position = glm::vec3(0.f);
		transform.eulerAngles = glm::vec3(0.f);
		transform.scale = glm::vec3(1.f);
		transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.localPosition = glm::vec3(0.f);
		transform.localEulerAngles = glm::vec3(0.f);
		transform.localScale = glm::vec3(1.f);
		transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.forward = glm::vec3(0.f, 0.f, 1.f);
		transform.up = glm::vec3(0.f, 1.f, 0.f);
		transform.right = glm::vec3(1.f, 0.f, 0.f);

		matrix.model = glm::mat4(1.f);
		matrix.translate = glm::mat4(1.f);
		matrix.rotationX = glm::mat4(1.f);
		matrix.rotationY = glm::mat4(1.f);
		matrix.rotationZ = glm::mat4(1.f);
		matrix.scale = glm::mat4(1.f);

		uniformModel = 0;
		uniformView = 0;
		uniformProjection = 0;

		UpdateTransform();
		UpdateMatrix();
	}

	Entity::Entity(std::vector<Vertex> vertexs, std::vector<uint> indexes, Render* render)
	{
		this->render = render;

		this->vertexs = vertexs;
		this->indexes = indexes;

		VAO = 0;
		VBO = 0;
		EBO = 0;

		name = "";

		parent = nullptr;
		nodes = std::list<Entity*>();

		transform.position = glm::vec3(0.f);
		transform.eulerAngles = glm::vec3(0.f);
		transform.scale = glm::vec3(1.f);
		transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.localPosition = glm::vec3(0.f);
		transform.localEulerAngles = glm::vec3(0.f);
		transform.localScale = glm::vec3(1.f);
		transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.forward = glm::vec3(0.f, 0.f, 1.f);
		transform.up = glm::vec3(0.f, 1.f, 0.f);
		transform.right = glm::vec3(1.f, 0.f, 0.f);

		matrix.model = glm::mat4(1.f);
		matrix.translate = glm::mat4(1.f);
		matrix.rotationX = glm::mat4(1.f);
		matrix.rotationY = glm::mat4(1.f);
		matrix.rotationZ = glm::mat4(1.f);
		matrix.scale = glm::mat4(1.f);

		uniformModel = 0;
		uniformView = 0;
		uniformProjection = 0;

		UpdateTransform();
		UpdateMatrix();
	}

	Entity::~Entity()
	{
		nodes.clear();
	}

	void Entity::SetName(std::string name)
	{
		this->name = name;
	}

	void Entity::SetParent(Entity* parent)
	{
		this->parent = parent;
	}

	void Entity::AddNode(Entity* node)
	{
		nodes.push_back(node);
	}

	void Entity::RemoveNode(Entity* node)
	{
		nodes.remove(node);
	}

	void Entity::RemoveNode(std::string nodeName)
	{
		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			if ((*it)->GetName() == nodeName)
			{
				nodes.remove((*it));
				return;
			}
		}
	}

	void Entity::RemoveNode(int nodeIndex)
	{
		if (nodeIndex > 0 && nodeIndex < nodes.size())
		{
			std::list<Entity*>::iterator it = nodes.begin();
			std::advance(it, nodeIndex);
			nodes.remove((*it));
		}
	}

	void Entity::SetPos(glm::vec3 pos)
	{
		transform.localPosition = pos;

		if (parent != nullptr)
		{
			transform.position = parent->GetPos() + transform.localPosition;
		}
		else
		{
			transform.position = transform.localPosition;
		}

		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
		UpdateMatrix();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->UpdateNodesPos();
		}
	}

	void Entity::SetRot(glm::vec3 rot)
	{
		transform.localEulerAngles = rot;

		if (parent != nullptr)
		{
			transform.eulerAngles = parent->GetRot() + transform.localEulerAngles;
		}
		else
		{
			transform.eulerAngles = transform.localEulerAngles;
		}

		matrix.rotationX = glm::rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1.f, 0.f, 0.f));
		matrix.rotationY = glm::rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0.f, 1.f, 0.f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0.f, 0.f, 1.f));

		UpdateTransform();
		UpdateMatrix();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->UpdateNodesRot();
		}
	}

	void Entity::SetScale(glm::vec3 scale)
	{
		transform.localScale = scale;

		if (parent != nullptr)
		{
			transform.scale = parent->GetScale() * transform.localScale;
		}
		else
		{
			transform.scale = transform.localScale;
		}

		matrix.scale = glm::scale4(glm::mat4(1.f), transform.scale);
		UpdateMatrix();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->UpdateNodesScale();
		}
	}

	void Entity::SetPos(float x, float y, float z)
	{
		SetPos({ x, y, z });
	}

	void Entity::SetPosX(float x)
	{
		SetPos(glm::vec3(x, GetPosY(), GetPosZ()));
	}

	void Entity::SetPosY(float y)
	{
		SetPos(glm::vec3(GetPosX(), y, GetPosZ()));
	}

	void Entity::SetPosZ(float z)
	{
		SetPos(glm::vec3(GetPosX(), GetPosY(), z));
	}

	void Entity::SetRot(float x, float y, float z)
	{
		SetRot(glm::vec3(x, y, z ));
	}

	void Entity::SetRotX(float x) 
	{
		SetRot(glm::vec3(x, GetRotY(), GetRotZ()));
	}

	void Entity::SetRotY(float y) 
	{
		SetRot(glm::vec3(GetRotX(), y, GetRotZ()));
	}

	void Entity::SetRotZ(float z) 
	{
		SetRot(glm::vec3(GetRotX(), GetRotY(), z));
	}

	void Entity::SetScale(float x, float y, float z)
	{
		SetScale(glm::vec3(x, y, z));
	}

	void Entity::SetScale(float size)
	{
		SetScale(glm::vec3(size, size, size));
	}

	std::string Entity::GetName()
	{
		return name;
	}

	Entity* Entity::GetParent()
	{
		return parent;
	}

	std::list<Entity*> Entity::GetNodes()
	{
		return nodes;
	}

	Entity* Entity::GetNode(std::string nodeName)
	{
		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			if ((*it)->GetName() == nodeName)
			{
				return (*it);
			}
		}

		return nullptr;
	}

	Entity* Entity::GetNode(int nodeIndex)
	{
		if (nodeIndex > 0 && nodeIndex < nodes.size())
		{
			std::list<Entity*>::iterator it = nodes.begin();
			std::advance(it, nodeIndex);
			
			return (*it);
		}

		return nullptr;
	}

	std::vector<Vertex> Entity::GetVertexs()
	{
		return vertexs;
	}

	std::vector<uint> Entity::GetIndexes()
	{
		return indexes;
	}

	glm::vec3 Entity::GetForward()
	{
		return transform.forward;
	}

	glm::vec3 Entity::GetUp()
	{
		return transform.up;
	}

	glm::vec3 Entity::GetRight()
	{
		return transform.right;
	}

	glm::vec3 Entity::GetPos()
	{
		return transform.position;
	}

	glm::vec3 Entity::GetRot()
	{
		return transform.eulerAngles;
	}

	glm::vec3 Entity::GetScale()
	{
		return transform.scale;
	}

	glm::vec3 Entity::GetLocalPosition()
	{
		return transform.localPosition;
	}

	glm::vec3 Entity::GetLocalRotation()
	{
		return transform.localEulerAngles;
	}

	glm::vec3 Entity::GetLocalScale()
	{
		return transform.localScale;
	}

	float Entity::GetPosX()
	{
		return transform.position.x;
	}

	float Entity::GetPosY()
	{
		return transform.position.y;
	}

	float Entity::GetPosZ()
	{
		return transform.position.z;
	}

	float Entity::GetRotX()
	{
		return transform.eulerAngles.x;
	}

	float Entity::GetRotY()
	{
		return transform.eulerAngles.y;
	}

	float Entity::GetRotZ()
	{
		return transform.eulerAngles.z;
	}

	float Entity::GetScaleX()
	{
		return transform.scale.x;
	}

	float Entity::GetScaleY()
	{
		return transform.scale.y;
	}

	float Entity::GetScaleZ()
	{
		return transform.scale.z;
	}

	void Entity::Draw()
	{
		render->Draw(VAO, indexes.size());
	}

	bool Entity::CheckVolume()
	{
		if (volume == nullptr) return true;

		return GetGlobalAABB()->IsOnFrustum(transform, matrix);
	}

	void Entity::GenerateVolumeAABB()
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

	VolumeAABB* Entity::GetGlobalAABB()
	{
		VolumeAABB* volumeAABB = static_cast<VolumeAABB*>(volume);

		//Get global scale thanks to our transform
		const glm::vec3 globalCenter{ matrix.model * glm::vec4(volumeAABB->center, 1.f) };

		// Scaled orientation
		const glm::vec3 right = transform.right * volumeAABB->extents.x;
		const glm::vec3 up = transform.up * volumeAABB->extents.y;
		const glm::vec3 forward = transform.forward * volumeAABB->extents.z;

		const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

		const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

		const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

		return new VolumeAABB(globalCenter, newIi, newIj, newIk);
	}

	void Entity::SetUniforms()
	{
		render->SetUniform(uniformModel, "model");
		render->SetUniform(uniformView, "view");
		render->SetUniform(uniformProjection, "projection");

		render->SetLocation(locationPosition, "aPos");
		render->SetLocation(locationNormal, "aNor");
		render->SetLocation(locationTexCoord, "aTex");
	}

	void Entity::UpdateShader()
	{
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
	}

	glm::quat Entity::EulerToQuat(glm::vec3 euler)
	{
		euler *= deg2rad;

		float cy = cos(euler.z * 0.5f);
		float sy = sin(euler.z * 0.5f);
		float cp = cos(euler.x * 0.5f);
		float sp = sin(euler.x * 0.5f);
		float cr = cos(euler.y * 0.5f);
		float sr = sin(euler.y * 0.5f);

		glm::quat q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = cr * sp * cy + sr * cp * sy;
		q.y = sr * cp * cy - cr * sp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		return q;
	}

	glm::vec3 Entity::QuatToVec(glm::quat quat, glm::vec3 vec)
	{
		float x2 = quat.x * 2.f;
		float y2 = quat.y * 2.f;
		float z2 = quat.z * 2.f;
		float xx2 = quat.x * x2;
		float yy2 = quat.y * y2;
		float zz2 = quat.z * z2;
		float xy2 = quat.x * y2;
		float xz2 = quat.x * z2;
		float yz2 = quat.y * z2;
		float wx2 = quat.w * x2;
		float wy2 = quat.w * y2;
		float wz2 = quat.w * z2;

		glm::vec3 res;
		res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
		res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
		res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
		return res;
	}

	void Entity::UpdateMatrix()
	{
		if (parent == nullptr)
		{
			glm::mat4 rot = matrix.rotationY * matrix.rotationX * matrix.rotationZ;
			matrix.model = matrix.translate * rot * matrix.scale;
		}
		else
		{
			glm::mat4 rot = matrix.rotationY * matrix.rotationX * matrix.rotationZ;
			glm::mat4 auxModel = matrix.translate * rot * matrix.scale;
			matrix.model = parent->matrix.model * auxModel;
		}
	}

	void Entity::UpdateTransform()
	{
		transform.rotation = EulerToQuat(transform.eulerAngles);
		transform.forward = QuatToVec(transform.rotation, glm::vec3(0.f, 0.f, 1.f));
		transform.up = QuatToVec(transform.rotation, glm::vec3(0.f, 1.f, 0.f));
		transform.right = QuatToVec(transform.rotation, glm::vec3(1.f, 0.f, 0.f));
	}

	void Entity::UpdateNodesPos()
	{
		transform.position = parent->GetPos() + transform.localPosition;
		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
		UpdateMatrix();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->UpdateNodesPos();
		}
	}

	void Entity::UpdateNodesRot()
	{
		transform.eulerAngles = parent->GetRot() + transform.localEulerAngles;

		matrix.rotationX = glm::rotate(glm::mat4(1.f), glm::radians(transform.eulerAngles.x), glm::vec3(1.f, 0.f, 0.f));
		matrix.rotationY = glm::rotate(glm::mat4(1.f), glm::radians(transform.eulerAngles.y), glm::vec3(0.f, 1.f, 0.f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(transform.eulerAngles.z), glm::vec3(0.f, 0.f, 1.f));

		UpdateTransform();
		UpdateMatrix();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->UpdateNodesRot();
		}
	}

	void Entity::UpdateNodesScale()
	{
		transform.scale = parent->GetScale() * transform.localScale;
		matrix.scale = glm::scale4(glm::mat4(1.f), transform.scale);
		UpdateMatrix();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->UpdateNodesScale();
		}
	}
}