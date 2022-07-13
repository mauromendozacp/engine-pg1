#include "occlusionCulling.h"

namespace GL
{
	Camera* OcclusionCulling::camera = nullptr;

	Plane OcclusionCulling::up = Plane();
	Plane OcclusionCulling::down = Plane();
	Plane OcclusionCulling::left = Plane();
	Plane OcclusionCulling::right = Plane();
	Plane OcclusionCulling::front = Plane();
	Plane OcclusionCulling::back = Plane();

	OcclusionCulling::OcclusionCulling()
	{
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

	void OcclusionCulling::Init(Camera* cam)
	{
		camera = cam;
	}

	void OcclusionCulling::Update()
	{
		float fov = camera->GetFOV();
		float aspect = camera->GetAspect();

		float halfheight = camera->GetFar() * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
		float halfWidth = halfheight * aspect;
		glm::vec3 frontFar = camera->GetFar() * camera->GetForward();

		back.SetPositionAndNormal(camera->GetPos() + camera->GetNear() * camera->GetForward(), camera->GetForward());
		front.SetPositionAndNormal(camera->GetPos() + frontFar, -camera->GetForward());
		right.SetPositionAndNormal(camera->GetPos(), glm::cross(camera->GetUp(), frontFar + camera->GetRight() * halfWidth));
		left.SetPositionAndNormal(camera->GetPos(), glm::cross(frontFar - camera->GetRight() * halfWidth, camera->GetUp()));
		up.SetPositionAndNormal(camera->GetPos(), glm::cross(camera->GetRight(), frontFar - camera->GetUp() * halfheight));
		down.SetPositionAndNormal(camera->GetPos(), glm::cross(frontFar + camera->GetUp() * halfheight, camera->GetRight()));
	}

	void OcclusionCulling::SetCamera(Camera* cam)
	{
		camera = cam;
	}
}