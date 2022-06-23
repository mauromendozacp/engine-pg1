#include "occlusionCulling.h"

namespace GL
{
	Camera* OcclusionCulling::camera = nullptr;

	glm::vec3 OcclusionCulling::pointBack = glm::vec3();
	glm::vec3 OcclusionCulling::pointFront = glm::vec3();
	glm::vec3 OcclusionCulling::pointTopLeft = glm::vec3();
	glm::vec3 OcclusionCulling::pointTopRight = glm::vec3();
	glm::vec3 OcclusionCulling::pointBottomLeft = glm::vec3();
	glm::vec3 OcclusionCulling::pointBottomRight = glm::vec3();

	Plane OcclusionCulling::up = Plane();
	Plane OcclusionCulling::down = Plane();
	Plane OcclusionCulling::left = Plane();
	Plane OcclusionCulling::right = Plane();
	Plane OcclusionCulling::front = Plane();
	Plane OcclusionCulling::back = Plane();

	OcclusionCulling::OcclusionCulling()
	{
		camera = nullptr;

		pointBack = glm::vec3();
		pointFront = glm::vec3();
		pointTopLeft = glm::vec3();
		pointTopRight = glm::vec3();
		pointBottomLeft = glm::vec3();
		pointBottomRight = glm::vec3();

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

	void OcclusionCulling::Init(Camera* cam)
	{
		camera = cam;
	}

	void OcclusionCulling::Update()
	{
		float fov = camera->GetFOV();
		float aspect = camera->GetAspect();

		float halfheight = camera->GetFar() * tan(fov * .5f);
		float halfWidth = halfheight * aspect;
		glm::vec3 frontFar = camera->GetFar() * camera->GetForward();

		back.SetPositionAndNormal(camera->GetPos() + camera->GetNear() * camera->GetForward(), camera->GetForward());
		front.SetPositionAndNormal(camera->GetPos() + frontFar, -camera->GetForward());
		right.SetPositionAndNormal(camera->GetPos(), glm::cross(camera->GetUp(), frontFar + camera->GetRight() * halfWidth));
		left.SetPositionAndNormal(camera->GetPos(), glm::cross(frontFar - camera->GetRight() * halfWidth, camera->GetUp()));
		up.SetPositionAndNormal(camera->GetPos(), glm::cross(camera->GetRight(), frontFar - camera->GetUp() * halfheight));
		down.SetPositionAndNormal(camera->GetPos(), glm::cross(frontFar + camera->GetUp() * halfheight, camera->GetRight()));

		/*pointBack = camera->GetPos() + camera->GetForward() * camera->GetNear();
		pointFront = camera->GetPos() + camera->GetForward() * camera->GetFar();

		float angleY = fov / 2;
		float halfHeight = (tan(angleY * glm::pi<float>() / 180)) * camera->GetFar();
		float halfWidth = halfHeight * aspect;

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
		left.Flip();*/
	}

	void OcclusionCulling::SetCamera(Camera* cam)
	{
		camera = cam;
	}
}