#include "shape.h"

namespace GL
{
	Shape::Shape(Render* render) : Entity2D(render)
	{
	}

	Shape::~Shape()
	{
	}

	void Shape::Init(SHAPE_TYPE shapeType)
	{
		switch (shapeType)
		{
		case SHAPE_TYPE::TRIANGLE:
			float vertex[]
			{
				// positions         // colors
				 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // bottom right
				-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // bottom left
				 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f    // top 
			};
			unsigned int indexes[]
			{
				0, 1, 2
			};
			vertices = 3;

			render->BindBuffer(VAO, VBO, sizeof(vertex) * 18, vertex);
			render->BindIndexs(EBO, sizeof(indexes) * 3, indexes);
			BindAttrib();

			break;
		}
	}

	void Shape::Draw()
	{
		unsigned int shaderId = render->GetSolidShaderId();
		render->UseShaderId(shaderId);
		SetShader(shaderId);
		Entity::Draw(shaderId);
	}

	void Shape::SetShader(unsigned int shaderId)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shaderId, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shaderId, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));
	}

	void Shape::BindAttrib()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
}