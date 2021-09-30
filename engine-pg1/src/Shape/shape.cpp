#include "shape.h"

namespace GL
{
	Shape::Shape(Render* render, SHAPE_TYPE shapeType) : Entity2D(render)
	{
		this->render = render;
		this->shapeType = shapeType;

		this->VBO = 0;
		this->VAO = 0;
		this->EBO = 0;
	}

	Shape::~Shape()
	{
		render->UnBind(VAO, VBO, EBO);
	}

	void Shape::Init()
	{
		float* vertex;
		unsigned int* indexes;

		switch (shapeType)
		{
		case SHAPE_TYPE::TRIANGLE:
			vertex = new float[18]
			{
				// positions         // colors
				 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
				 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
			};
			indexes = new unsigned int[3]
			{
				0, 1, 2
			};
			vertices = 3;

			render->BindBuffer(VAO, VBO, sizeof(vertex) * 18, vertex);
			render->BindIndexs(EBO, sizeof(indexes) * 3, indexes);
			render->BindAttrib();

			delete[] vertex;
			delete[] indexes;

			break;
		default:
			break;
		}
	}

	void Shape::Draw()
	{
		render->Draw(model, color, VAO, vertices);
	}
}