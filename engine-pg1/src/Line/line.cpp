#include "line.h"

namespace GL
{
	Line::Line()
	{
		render = nullptr;
		color = Color(124, 252, 0);

		VAO = 0;
		VBO = 0;

		vertexs = std::vector<Vertex>();

		locationPosition = 0;
		uniformColor = 0;
		uniformAlpha = 0;
	}

	Line::Line(Render* render)
	{
		this->render = render;
		color = Color(124, 252, 0);

		VAO = 0;
		VBO = 0;

		vertexs = std::vector<Vertex>();

		locationPosition = 0;
		uniformColor = 0;
		uniformAlpha = 0;
	}

	Line::Line(std::vector<Vertex> vertexs, Render* render)
	{
		this->render = render;
		this->vertexs = vertexs;

		color = Color(125, 255, 0);

		VAO = 0;
		VBO = 0;

		locationPosition = 0;
		uniformColor = 0;
		uniformAlpha = 0;
	}

	Line::~Line()
	{
	}

	void Line::Init()
	{
		SetUniforms();

		render->GenBuffers(VAO, VBO);
		render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);

		render->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
	}

	void Line::Draw()
	{
		render->UseShader();
		UpdateShader();
		render->DrawLines(VAO, vertexs.size());
		render->CleanShader();
	}

	void Line::DeInit()
	{
		render->UnBind(VAO, VBO);

		vertexs.clear();
	}

	std::vector<Vertex> Line::GetVertexs()
	{
		return vertexs;
	}

	void Line::SetUniforms()
	{
		render->SetLocation(locationPosition, "aPos");

		render->SetUniform(uniformColor, "color");
		render->SetUniform(uniformAlpha, "a");
	}

	void Line::UpdateShader()
	{
		render->UpdateColor(uniformColor, uniformAlpha, color.GetColor());
	}
}