#include "shape.h"

namespace GL
{
	Shape::Shape() : Entity2D()
	{
	}

	Shape::Shape(Render* render) : Entity2D(render)
	{
	}

	Shape::~Shape()
	{
	}

	void Shape::Init(SHAPE_TYPE shapeType)
	{
		useTexture = false;
		SetUniforms();

		uint* indexes;

		switch (shapeType)
		{
		case SHAPE_TYPE::TRIANGLE:
			
			indexes = triangIndexes;
			vertices = triangIndexTam;
			vertexs = triangVertex;
			tam = sizeof(vertexs) * triangVertTam;

			break;
		case SHAPE_TYPE::QUAD:

			indexes = quadIndexes;
			vertices = quadIndexTam;
			vertexs = quadVertex;
			tam = sizeof(vertexs) * quadVertTam;

			break;
		case SHAPE_TYPE::CUBE:

			indexes = cubeIndexes;
			vertices = cubeIndexTam;
			vertexs = cubeVertex;
			tam = sizeof(vertexs) * cubeVertTam;

			break;
		default:
			return;
		}

		render->GenBuffers(VAO, VBO, EBO);
		render->BindBuffer(VAO, VBO, tam, vertexs);
		render->BindIndexs(EBO, sizeof(indexes) * vertices, indexes);

		render->SetBaseAttribs(locationPosition, 3, 6 * sizeof(float), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	void Shape::Draw()
	{
		render->UseShader();
		UpdateShader();
		Entity2D::Draw();
		render->CleanShader();
	}

	void Shape::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);
	}
}