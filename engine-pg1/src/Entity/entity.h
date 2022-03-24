#ifndef ENTITY_H
#define ENTITY_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include <../glm/gtc/type_ptr.hpp>

namespace GL
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 eulerAngles;
		glm::vec3 scale;
		glm::quat rotation;

		glm::vec3 localPosition;
		glm::vec3 localEulerAngles;
		glm::vec3 localScale;
		glm::quat localRotation;

		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	struct Matrix
	{
		glm::mat4 model;
		glm::mat4 translate;
		glm::mat4 rotationX;
		glm::mat4 rotationY;
		glm::mat4 rotationZ;
		glm::mat4 scale;
	};

	class GRAPHICSENGINE_API Entity
	{
	public:
		Entity();
		Entity(Render* render);
		~Entity();

		void SetPos(glm::vec3 pos);
		void SetRot(glm::vec3 rot);
		void SetScale(glm::vec3 scale);

		void SetPos(float x, float y, float z);
		void SetRot(float x, float y, float z);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		void SetScale(float x, float y, float z);
		void SetScale(float size);

		glm::vec3 GetPos();
		glm::vec3 GetRot();
		glm::vec3 GetScale();

		float GetPosX();
		float GetPosY();
		float GetPosZ();

		float GetRotX();
		float GetRotY();
		float GetRotZ();

		float GetScaleX();
		float GetScaleY();
		float GetScaleZ();

	protected:
		Render* render;

		Transform transform;
		Matrix matrix;

		uint uniformModel;
		uint uniformView;
		uint uniformProjection;
		uint uniformPosition;
		uint uniformNormal;
		uint uniformTexCoord;

		virtual void SetUniforms();

		glm::quat EulerToQuat(glm::vec3 euler);
		glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);

		void UpdateMatrix();
		void UpdateTransform();
	};
}

#endif // !ENTITY_H