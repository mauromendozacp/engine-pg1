#include "color.h"

namespace GL
{
	const int colorValue = 255;

	Color::Color()
	{
		r = 1.f;
		g = 1.f;
		b = 1.f;
		a = 1.f;
	}

	Color::~Color()
	{
	}

	void Color::SetColor(int r, int g, int b)
	{
		this->r = glm::clamp(r, 0, colorValue) / colorValue;
		this->g = glm::clamp(g, 0, colorValue) / colorValue;
		this->b = glm::clamp(b, 0, colorValue) / colorValue;
	}

	void Color::SetColor(int r, int g, int b, int a)
	{
		SetColor(r, g, b);
		this->a = glm::clamp(a, 0, colorValue) / colorValue;
	}

	void Color::SetColor(float r, float g, float b)
	{
		this->r = glm::clamp(r, 0.f, 1.f);
		this->g = glm::clamp(g, 0.f, 1.f);
		this->b = glm::clamp(b, 0.f, 1.f);
	}

	void Color::SetColor(float r, float g, float b, float a)
	{
		SetColor(r, g, b);
		this->a = glm::clamp(a, 0.f, 1.f);
	}

	glm::vec4 Color::GetColor()
	{
		return glm::vec4(r, g, b, a);
	}
}