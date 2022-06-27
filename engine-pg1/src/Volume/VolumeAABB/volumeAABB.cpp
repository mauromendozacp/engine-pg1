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

	bool VolumeAABB::IsOnFrustum(glm::mat4 worldModel)
	{
		glm::vec3 globalCenter { worldModel * glm::vec4(center, 1.f) };

		glm::vec3 right = worldModel[0] * extents.x;
		glm::vec3 up = worldModel[1] * extents.y;
		glm::vec3 forward = worldModel[2] * extents.z;

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

		return (globalAABB.IsOnPlane(OcclusionCulling::left) &&
			globalAABB.IsOnPlane(OcclusionCulling::right) &&
			globalAABB.IsOnPlane(OcclusionCulling::up) &&
			globalAABB.IsOnPlane(OcclusionCulling::down) &&
			globalAABB.IsOnPlane(OcclusionCulling::back) &&
			globalAABB.IsOnPlane(OcclusionCulling::front));
	}

	bool VolumeAABB::IsOnPlane(Plane plane)
	{
		float r = extents.x * std::abs(plane.GetNormal().x) + extents.y * std::abs(plane.GetNormal().y) + extents.z * std::abs(plane.GetNormal().z);
		
		return -r <= plane.GetDistanceToPoint(center);
	}
}
