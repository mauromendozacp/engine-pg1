#include "occlusionCulling.h"

namespace GL
{
	OcclusionCulling::OcclusionCulling()
	{
		entities = std::list<Entity*>();
		camera = nullptr;

		up = Plane();
		down = Plane();
		left = Plane();
		right = Plane();
		front = Plane();
		back = Plane();
	}

	OcclusionCulling::~OcclusionCulling()
	{
	}

	void OcclusionCulling::Init(Camera* camera)
	{
		this->camera = camera;
	}

	void OcclusionCulling::Update()
	{
		UpdatePlanes();

		for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			UpdateEntitiesDraw((*it));
		}
	}

	void OcclusionCulling::SetCamera(Camera* camera)
	{
		this->camera = camera;
	}

	void OcclusionCulling::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void OcclusionCulling::UpdatePlanes()
	{
		pointBack = camera->GetPos() + camera->GetForward() * camera->GetNear();
		pointFront = camera->GetPos() + camera->GetForward() * camera->GetFar();

		float angleY = camera->GetFOV() / 2;
		float halfHeight = (tan(angleY * glm::pi<float>() / 180)) * camera->GetFar();
		float halfWidth = halfHeight * camera->GetAspect();

		pointTopLeft = pointFront + (camera->GetUp() * halfHeight) - (camera->GetRight() * halfWidth);
		pointTopRight = pointFront + (camera->GetUp() * halfHeight) + (camera->GetRight() * halfWidth);
		pointBottomLeft = pointFront - (camera->GetUp() * halfHeight) - (camera->GetRight() * halfWidth);
		pointBottomRight = pointFront - (camera->GetUp() * halfHeight) + (camera->GetRight() * halfWidth);

		up.Set3Points(pointTopLeft, pointTopRight, camera->GetPos());
		down.Set3Points(pointBottomLeft, pointBottomRight, camera->GetPos());
		left.Set3Points(pointTopLeft, pointBottomLeft, camera->GetPos());
		right.Set3Points(pointTopRight, pointBottomRight, camera->GetPos());
		front.SetNormalAndPosition(glm::normalize(pointBack - pointFront), pointFront);
		back.SetNormalAndPosition(glm::normalize(pointFront - pointBack), pointBack);

		down.Flip();
		left.Flip();
	}

	void OcclusionCulling::UpdateEntitiesDraw(Entity* entity)
	{
		glm::vec3 pos = entity->GetPos();

		if (up.GetSide(pos) && down.GetSide(pos) && left.GetSide(pos) && right.GetSide(pos) && front.GetSide(pos) && back.GetSide(pos))
		{
			entity->SetCanDraw(true);
		}
		else
		{
			entity->SetCanDraw(false);
		}

		std::list<Entity*> nodes = entity->GetNodes();
		if (nodes.size() > 0)
		{
			for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
			{
				UpdateEntitiesDraw((*it));
			}
		}
	}
}