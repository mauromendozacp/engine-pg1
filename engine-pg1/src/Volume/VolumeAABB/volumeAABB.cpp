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

	bool VolumeAABB::IsOnFrustum(glm::mat4 model)
	{
		glm::vec3 globalCenter { model * glm::vec4(center, 1.f) };

		glm::vec3 right = model[0] * extents.x;
		glm::vec3 up = model[1] * extents.y;
		glm::vec3 forward = model[2] * extents.z;

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

	void VolumeAABB::Draw()
	{
		lines.Draw();
	}

	std::vector<Vertex> VolumeAABB::GetVertexs()
	{
		glm::vec3 vertice[8];
		vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
		vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
		vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
		vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
		vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
		vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
		vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
		vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };

		std::vector<Vertex> vertexs = std::vector<Vertex>();
		for (int i = 0; i < 8; i++)
		{
			Vertex vertex;
			vertex.Position = vertice[i];
			vertex.Normal = glm::vec3(1.f, 1.f, 1.f);
			vertexs.push_back(vertex);
		}

		return vertexs;
	}

	bool VolumeAABB::IsOnPlane(Plane plane)
	{
		float r = extents.x * std::abs(plane.GetNormal().x) + extents.y * std::abs(plane.GetNormal().y) + extents.z * std::abs(plane.GetNormal().z);
		
		return -r <= plane.GetDistanceToPoint(center);
	}
}
