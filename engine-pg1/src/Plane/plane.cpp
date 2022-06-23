#include "plane.h"

namespace GL
{
	Plane::Plane()
	{
		normal = glm::vec3();
		distance = 0.f;
	}

	Plane::Plane(glm::vec3 normal, glm::vec3 point)
	{
		this->normal = glm::normalize(normal);
		distance = -glm::dot(normal, point);
	}

	Plane::Plane(glm::vec3 normal, float distance)
	{
		this->normal = glm::normalize(normal);
		this->distance = distance;
	}

	Plane::Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c)
	{
		normal = glm::normalize(glm::cross(b - a, c - a));
		distance = -glm::dot(normal, a);
	}

	Plane::~Plane()
	{
	}

	void Plane::SetNormal(glm::vec3 normal)
	{
		this->normal = normal;
	}

	void Plane::SetDistance(float distance)
	{
		this->distance = distance;
	}

	glm::vec3 Plane::GetNormal()
	{
		return normal;
	}

	float Plane::GetDistance()
	{
		return distance;
	}

	void Plane::SetNormalAndPosition(glm::vec3 normal, glm::vec3 point)
	{
		this->normal = glm::normalize(normal);
		distance = -glm::dot(this->normal, point);
	}

	void Plane::Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c)
	{
		normal = glm::normalize(glm::cross(b - a, c - a));
		distance = -glm::dot(normal, a);
	}

	void Plane::Flip()
	{
		normal = -normal;
		distance = -distance;
	}

	void Plane::Translate(glm::vec3 translation)
	{
		distance += glm::dot(normal, translation);
	}

	glm::vec3 Plane::ClosestPointOnPlane(glm::vec3 point)
	{
		float pointToPlaneDistance = glm::dot(normal, point) + distance;
		return point - (normal * pointToPlaneDistance);
	}

	float Plane::GetDistanceToPoint(glm::vec3 point)
	{
		return glm::dot(normal, point) + distance;
	}

	bool Plane::GetSide(glm::vec3 point)
	{
		return glm::dot(normal, point) + distance > 0.f;
	}

	bool Plane::SameSide(glm::vec3 point1, glm::vec3 point2)
	{
		float d0 = GetDistanceToPoint(point1);
		float d1 = GetDistanceToPoint(point2);
		return (d0 > 0.0f && d1 > 0.0f) || (d0 <= 0.0f && d1 <= 0.0f);;
	}
}