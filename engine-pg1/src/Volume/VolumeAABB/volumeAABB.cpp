#include "volumeAABB.h"
#include "OcclusionCulling/occlusionCulling.h"

namespace GL
{
	VolumeAABB::VolumeAABB() : Volume()
	{
		center = glm::vec3();
		extents = glm::vec3();
	}

	VolumeAABB::VolumeAABB(glm::vec3 min, glm::vec3 max)
	{
		center = glm::vec3((max + min) * .5f);
		extents = glm::vec3(max.x - center.x, max.y - center.y, max.z - center.z);
	}

	VolumeAABB::VolumeAABB(glm::vec3 center, float extX, float extY, float extZ)
	{
		this->center = center;
		extents = glm::vec3(extX, extY, extZ);
	}

	VolumeAABB::~VolumeAABB()
	{
	}

	bool VolumeAABB::IsOnFrustum(Transform transform, glm::mat4 worldModel)
	{
		glm::vec3 globalCenter { worldModel * glm::vec4(center, 1.f) };

		glm::vec3 right = transform.right * extents.x;
		glm::vec3 up = transform.up * extents.y;
		glm::vec3 forward = transform.forward * extents.z;

		float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

		float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

		float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

		VolumeAABB globalAABB(globalCenter, newIi, newIj, newIk);

		glm::vec3 aabbPositions[MAX_BOUNDS];
		aabbPositions[0] = globalAABB.center + glm::vec3(-globalAABB.extents.x, -globalAABB.extents.y, globalAABB.extents.z);
		aabbPositions[1] = globalAABB.center + glm::vec3(globalAABB.extents.x, -globalAABB.extents.y, globalAABB.extents.z);
		aabbPositions[2] = globalAABB.center + glm::vec3(-globalAABB.extents.x, globalAABB.extents.y, globalAABB.extents.z);
		aabbPositions[3] = globalAABB.center + glm::vec3(globalAABB.extents.x, globalAABB.extents.y, globalAABB.extents.z);
		aabbPositions[4] = globalAABB.center + glm::vec3(-globalAABB.extents.x, -globalAABB.extents.y, -globalAABB.extents.z);
		aabbPositions[5] = globalAABB.center + glm::vec3(globalAABB.extents.x, -globalAABB.extents.y, -globalAABB.extents.z);
		aabbPositions[6] = globalAABB.center + glm::vec3(-globalAABB.extents.x, globalAABB.extents.y, -globalAABB.extents.z);
		aabbPositions[7] = globalAABB.center + glm::vec3(globalAABB.extents.x, globalAABB.extents.y, -globalAABB.extents.z);

		for (int i = 0; i < MAX_BOUNDS; i++)
		{
			if (OcclusionCulling::left.GetSide(aabbPositions[i]) &&
				OcclusionCulling::right.GetSide(aabbPositions[i]) &&
				OcclusionCulling::up.GetSide(aabbPositions[i]) &&
				OcclusionCulling::down.GetSide(aabbPositions[i]) &&
				OcclusionCulling::back.GetSide(aabbPositions[i]) &&
				OcclusionCulling::front.GetSide(aabbPositions[i]))
			{
				return true;
			}
		}

		return false;
	}

	bool VolumeAABB::IsOnPlane(Plane plane)
	{
		float r = extents.x * std::abs(plane.GetNormal().x) + extents.y * std::abs(plane.GetNormal().y) + extents.z * std::abs(plane.GetNormal().z);
		
		return -r <= plane.GetDistanceToPoint(center);
	}
}
