#include "entity.h"

namespace GL
{
	const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;

	Entity::Entity()
	{
		render = nullptr;

		transform.position = glm::vec3(0.f);
		transform.eulerAngles = glm::vec3(0.f);
		transform.scale = glm::vec3(1.f);
		transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.localPosition = glm::vec3(0.f);
		transform.localEulerAngles = glm::vec3(0.f);
		transform.localScale = glm::vec3(1.f);
		transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.forward = glm::vec3(0.f);
		transform.up = glm::vec3(0.f);
		transform.right = glm::vec3(0.f);

		matrix.model = glm::mat4(1.f);
		matrix.translate = glm::mat4(1.f);
		matrix.rotationX = glm::mat4(1.f);
		matrix.rotationY = glm::mat4(1.f);
		matrix.rotationZ = glm::mat4(1.f);
		matrix.scale = glm::mat4(1.f);

		uniformModel = 0;
		uniformView = 0;
		uniformProjection = 0;

		UpdateMatrix();
	}

	Entity::Entity(Render* render)
	{
		this->render = render;

		transform.position = glm::vec3(0.f);
		transform.eulerAngles = glm::vec3(0.f);
		transform.scale = glm::vec3(1.f);
		transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.localPosition = glm::vec3(0.f);
		transform.localEulerAngles = glm::vec3(0.f);
		transform.localScale = glm::vec3(1.f);
		transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

		transform.forward = glm::vec3(0.f);
		transform.up = glm::vec3(0.f);
		transform.right = glm::vec3(0.f);

		matrix.model = glm::mat4(1.f);
		matrix.translate = glm::mat4(1.f);
		matrix.rotationX = glm::mat4(1.f);
		matrix.rotationY = glm::mat4(1.f);
		matrix.rotationZ = glm::mat4(1.f);
		matrix.scale = glm::mat4(1.f);

		uniformModel = 0;
		uniformView = 0;
		uniformProjection = 0;

		UpdateMatrix();
	}

	Entity::~Entity()
	{
	}

	void Entity::SetPos(glm::vec3 pos)
	{
		transform.position = pos;
		transform.localPosition = pos;
		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);

		UpdateMatrix();
		UpdateTransform();
	}

	void Entity::SetRot(glm::vec3 rot)
	{
		transform.rotation = rot;
		transform.localRotation = rot;
		matrix.rotationX = glm::rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1.f, 0.f, 0.f));
		matrix.rotationY = glm::rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0.f, 1.f, 0.f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0.f, 0.f, 1.f));

		UpdateMatrix();
		UpdateTransform();
	}

	void Entity::SetScale(glm::vec3 scale)
	{
		transform.scale = scale;
		transform.localScale = scale;
		matrix.scale = glm::scale(glm::mat4(1.f), transform.scale);
		
		UpdateMatrix();
		UpdateTransform();
	}

	void Entity::SetPos(float x, float y, float z)
	{
		SetPos({ x, y, z });
	}

	void Entity::SetRot(float x, float y, float z)
	{
		SetRot({ x, y, z });
	}

	void Entity::SetRotX(float x) 
	{
		transform.eulerAngles.x = x;
		transform.localEulerAngles.x = x;
		matrix.rotationX = glm::rotate(glm::mat4(1.f), glm::radians(x), glm::vec3(1.f, 0.f, 0.f));

		UpdateMatrix();
		UpdateTransform();
	}

	void Entity::SetRotY(float y) 
	{
		transform.eulerAngles.y = y;
		transform.localEulerAngles.y = y;
		matrix.rotationY = glm::rotate(glm::mat4(1.f), glm::radians(y), glm::vec3(0.f, 1.f, 0.f));

		UpdateMatrix();
		UpdateTransform();
	}

	void Entity::SetRotZ(float z) 
	{
		transform.eulerAngles.z = z;
		transform.localEulerAngles.z = z;
		matrix.rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(z), glm::vec3(0.f, 0.f, 1.f));

		UpdateMatrix();
		UpdateTransform();
	}

	void Entity::SetScale(float x, float y, float z)
	{
		SetScale({ x, y, z });
	}

	void Entity::SetScale(float size)
	{
		SetScale({ size, size, size });
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

	void Entity::SetUniforms(uint shaderId)
	{
		render->SetUniform(shaderId, uniformModel, "model");
		render->SetUniform(shaderId, uniformView, "view");
		render->SetUniform(shaderId, uniformProjection, "projection");
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
		matrix.model = matrix.translate * matrix.rotationX * matrix.rotationY * matrix.rotationZ * matrix.scale;
	}

	void Entity::UpdateTransform()
	{
		transform.rotation = EulerToQuat(transform.eulerAngles);
		transform.forward = QuatToVec(transform.rotation, glm::vec3(0.f, 0.f, 1.f));
		transform.up = QuatToVec(transform.rotation, glm::vec3(0.f, 1.f, 0.f));
		transform.right = QuatToVec(transform.rotation, glm::vec3(1.f, 0.f, 0.f));
	}
}