#include "shape.h"

namespace GL
{
	#pragma region TRIANGULE_VERTEX

	const int triangVertTam = 18;
	const int triangIndexTam = 3;
	static unsigned int triangIndexes[triangIndexTam]
	{
		0, 1, 2
	};
	static float triangVertex[triangVertTam]
	{
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f    // top 
	};

	#pragma endregion

	#pragma region QUAD_VERTEX

	const int quadVertTam = 24;
	const int quadIndexTam = 6;
	static unsigned int quadIndexes[quadIndexTam]
	{
		0, 1, 3,
		1, 2, 3
	};
	static float quadVertex[quadVertTam]
	{
		// positions          // colors        
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   // bottom right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   // bottom left
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   // top 
		-0.5f,  0.5f, 0.0f,	  1.0f, 1.0f, 1.0f,
	};

	#pragma endregion

	Shape::Shape(Render* render) : Entity2D(render)
	{
	}

	Shape::~Shape()
	{
	}

	void Shape::Init(SHAPE_TYPE shapeType)
	{
		unsigned int* indexes;

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
		default:
			return;
		}

		render->BindBuffer(VAO, VBO, tam, vertexs);
		render->BindIndexs(EBO, sizeof(indexes) * vertices, indexes);
		render->BindBaseAttrib();
	}

	void Shape::Draw()
	{
		unsigned int shaderId = render->GetSolidShaderId();
		render->UseShaderId(shaderId);
		render->SetShader(shaderId, color);
		Entity::Draw(shaderId);
	}
}