#include "volumeAABB.h"

namespace GL
{
	VolumeAABB::VolumeAABB() : Volume()
	{
		center = glm::vec3();
		extents = glm::vec3();
	}

	VolumeAABB::VolumeAABB(glm::vec3 min, glm::vec3 max)
	{
		center = glm::vec3((max + min) * 0.5f);
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

	bool VolumeAABB::IsOnFrustum(Entity* entity)
	{
		glm::vec3 globalCenter { entity->matrix.model * glm::vec4(center, 1.f) };

		glm::vec3 right = entity->GetRight() * extents.x;
		glm::vec3 up = entity->GetUp() * extents.y;
		glm::vec3 forward = entity->GetForward() * extents.z;

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

	VolumeAABB VolumeAABB::GenerateVolumeAABB(Entity* entity)
	{
		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

		std::list<Entity*> nodes = entity->GetNodes();
		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			std::vector<Vertex> vertexs = (*it)->GetVertexs();
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
		}
		return VolumeAABB(minAABB, maxAABB);
	}

	bool VolumeAABB::IsOnPlane(Plane plane)
	{
		float r = extents.x * std::abs(plane.GetNormal().x) + extents.y * std::abs(plane.GetNormal().y) + extents.z * std::abs(plane.GetNormal().z);

		return -r <= plane.GetDistanceToPoint(center);
	}
}
