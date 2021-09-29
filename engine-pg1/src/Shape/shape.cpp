#include "shape.h"

namespace GL
{
	Shape::Shape(Render* render, SHAPE_TYPE shapeType) : Entity2D(render)
	{
		this->shapeType = shapeType;

		this->VBO = 0;
		this->VAO = 0;
		this->EBO = 0;

		this->vertices = 0;
		this->indices = 0;
	}

	Shape::~Shape()
	{
	}

	void Shape::Init()
	{
		this->render->BindBuffer(VAO, VBO, EBO, vertices);
		//this->render->RenderBuffer();
	}

	void Shape::Draw()
	{
		//this->render->UseShader();
		glBindVertexArray(VAO);

		switch (shapeType)
		{
		case SHAPE_TYPE::TRIANGLE:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		default:
			break;
		}

		glBindVertexArray(0);
		//this->render->UseShader();
	}
}