#ifndef ENTITY_H
#define ENTITY_H

#include "exports.h"
#include "Renderer/renderer.h"

#include "transform.h"
#include "matrix.h"
#include "vertexs.h"

#include "Volume/volume.h"
#include "Volume/VolumeAABB/volumeAABB.h"

#include "GLM/glm.hpp"
#include "GLM/ext/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtx/norm.hpp"

#include <list>
#include <vector>
#include <math.h>

namespace GL
{
	class GRAPHICSENGINE_API Entity
	{
	public:
		Entity();
		Entity(Render* render);
		~Entity();

		virtual void Update();
		virtual void Draw();
		virtual void DeInit();

		void SetParent(Entity* parent);
		void AddNode(Entity* node);
		void RemoveNode(Entity* node);
		void RemoveNode(std::string nodeName);
		void RemoveNode(int nodeIndex);

		void SetPos(glm::vec3 pos);
		void SetRot(glm::vec3 rot);
		void SetScale(glm::vec3 scale);

		void SetPos(float x, float y, float z);
		void SetPosX(float x);
		void SetPosY(float y);
		void SetPosZ(float z);

		void SetRot(float x, float y, float z);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);

		void SetScale(float x, float y, float z);
		void SetScale(float size);

		void SetMatrix(glm::mat4 mat);

		void LookTarget(glm::vec3 target);
		void SetDirection(glm::vec3 dir);

		Entity* GetParent();
		std::list<Entity*> GetNodes();
		Entity* GetNode(std::string nodeName);
		Entity* GetNode(int nodeIndex);

		Volume* GetGlobalVolume();
		void ToggleDrawVolume();
		void DrawVolume();

		glm::vec3 GetForward();
		glm::vec3 GetUp();
		glm::vec3 GetRight();

		glm::vec3 GetPos();
		glm::vec3 GetRot();
		glm::vec3 GetScale();

		glm::vec3 GetPos(glm::mat4 mat);
		glm::vec3 GetRot(glm::mat4 mat);
		glm::vec3 GetScale(glm::mat4 mat);

		glm::vec3 GetLocalPosition();
		glm::vec3 GetLocalRotation();
		glm::vec3 GetLocalScale();

		float GetPosX();
		float GetPosY();
		float GetPosZ();

		float GetRotX();
		float GetRotY();
		float GetRotZ();

		float GetScaleX();
		float GetScaleY();
		float GetScaleZ();

		void Reset();

		Matrix matrix;
		Transform transform;

		std::string name;
		bool enabled;
		bool visible;
		bool isOnFrustum;
		
	protected:
		Render* render;

		Entity* parent;
		std::list<Entity*> nodes;

		Volume* localVolume;
		Volume* globalVolume;
		bool volumeDirty;
		bool drawVolume;

		uint uniformModel;
		uint uniformView;
		uint uniformProjection;
		uint locationPosition;
		uint locationNormal;
		uint locationTexCoord;

		bool IsCanDraw();
		void UpdateGlobalVolume();

		virtual void SetUniforms();
		virtual void UpdateShader();

	private:
		glm::quat EulerToQuat(glm::vec3 euler);
		glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);

		glm::quat GetRotationByMatrix(glm::mat4 mat);
		glm::vec3 ToEulerRad(glm::quat rot);
		glm::vec3 NormalizeAngles(glm::vec3 angles);
		float NormalizeAngle(float angle);

		void UpdateMatrix();
		void UpdateTransform();

		void UpdateNodesPos();
		void UpdateNodesRot();
		void UpdateNodesScale();
	};
}

#endif // !ENTITY_H