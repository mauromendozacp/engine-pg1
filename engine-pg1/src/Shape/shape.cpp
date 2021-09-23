#include "shape.h"

namespace GL
{
	Shape::Shape(Render* render, SHAPE_TYPE shapeType) : Entity2D(render)
	{
		this->shapeType = shapeType;
	}

	Shape::~Shape()
	{
	}

	void Shape::Init()
	{
		this->render->BindBuffer(VAO, VBO, EBO, vertices);
		this->render->RenderBuffer();
	}

	void Shape::Draw()
	{
		this->render->UseShader();
		glBindVertexArray(VAO);

		switch (shapeType)
		{
		case GL::TRIANGLE:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		default:
			break;
		}

		glBindVertexArray(0);
		this->render->UseShader();
	}


}