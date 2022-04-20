#include "color.h"

namespace GL
{
	const float colorValue = 255.f;

	Color::Color()
	{
		r = 1.f;
		g = 1.f;
		b = 1.f;
		a = 1.f;
	}

	Color::Color(int r, int g, int b)
	{
		SetColor(r, g, b);
		a = 1.f;
	}

	Color::~Color()
	{
	}

	void Color::SetColor(int r, int g, int b)
	{
		this->r = glm::clamp(static_cast<float>(r), 0.f, colorValue) / colorValue;
		this->g = glm::clamp(static_cast<float>(g), 0.f, colorValue) / colorValue;
		this->b = glm::clamp(static_cast<float>(b), 0.f, colorValue) / colorValue;
	}

	void Color::SetColor(int r, int g, int b, int a)
	{
		SetColor(r, g, b);
		this->a = glm::clamp(static_cast<float>(a), 0.f, colorValue) / colorValue;
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

	glm::vec3 Color::GetColorRGB()
	{
		return glm::vec3(r, g, b);
	}

	Color Color::GetRandomColor()
	{
		int r = rand() % (static_cast<int>(colorValue) + 1);
		int g = rand() % (static_cast<int>(colorValue) + 1);
		int b = rand() % (static_cast<int>(colorValue) + 1);

		return Color(r, g, b);
	}
}