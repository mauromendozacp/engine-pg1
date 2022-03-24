#include "light.h"

namespace GL
{
	Light::Light(Render* render) : Entity(render)
	{
		color = glm::vec3(0.f);
		direction = glm::vec3(0.f);
		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);
	}

	Light::~Light()
	{
	}

	void Light::SetColor(glm::vec3 color)
	{
		this->color = color;
	}

	glm::vec3 Light::GetColor()
	{
		return color;
	}
}