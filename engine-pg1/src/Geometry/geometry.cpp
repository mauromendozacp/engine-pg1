#include "geometry.h"

namespace GL
{
	#pragma region CUBE_VERTEX

	const int cubeVertTam = 180;
	const int cubeIndexTam = 36;
	static unsigned int cubeIndexes[cubeIndexTam]
	{
		0, 1, 2,
		1, 2, 3,
		1, 4, 3,
		4, 5, 3,
		1, 6, 0,
		6, 7, 0,
		0, 2, 9,
		0, 8, 9,
		2, 3, 11,
		3, 10, 11,
		6, 7, 10,
		7, 10, 11,
	};
	static float cubeVertex[cubeVertTam]
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	#pragma endregion

	Geometry::Geometry()
	{
	}

	Geometry::Geometry(Render* render)
	{
	}

	Geometry::~Geometry()
	{
	}

	void Geometry::Init(GEOMETRY_TYPE geometryType)
	{
		unsigned int* indexes;

		switch (geometryType)
		{
		case GEOMETRY_TYPE::CUBE:

			indexes = cubeIndexes;
			vertices = cubeIndexTam;
			vertexs = cubeVertex;
			tam = sizeof(vertexs) * cubeVertTam;

			break;
		case GEOMETRY_TYPE::SPHERE:
			indexes = 0;
			break;
		case GEOMETRY_TYPE::CAPSULE:
			indexes = 0;
			break;
		default:
			return;
		}

		render->BindBuffer(VAO, VBO, tam, vertexs);
		render->BindIndexs(EBO, sizeof(indexes) * vertices, indexes);
		render->BindBaseAttrib();
	}

	void Geometry::Draw()
	{
		unsigned int shaderId = render->GetSolidShaderId();
		render->UseShaderId(shaderId);
		render->SetShader(shaderId, color);
		Entity::Draw(shaderId);
	}
}