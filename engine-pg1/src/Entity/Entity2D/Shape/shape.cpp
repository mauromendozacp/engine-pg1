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

		switch (shapeType)
		{
		case SHAPE_TYPE::TRIANGLE:
			for (int i = 0; i < triangVertexTam; i++)
			{
				Vertex vertex;
				vertex.Position = triangPositions[i];
				vertex.Normal = triangNormals[i];

				vertexs.push_back(vertex);
			}

			for (int i = 0; i < triangIndexTam; i++)
			{
				indexes.push_back(triangIndexes[i]);
			}

			break;
		case SHAPE_TYPE::QUAD:

			for (int i = 0; i < quadVertexTam; i++)
			{
				Vertex vertex;
				vertex.Position = quadPositions[i];
				vertex.Normal = quadNormals[i];

				vertexs.push_back(vertex);
			}

			for (int i = 0; i < quadIndexTam; i++)
			{
				indexes.push_back(quadIndexes[i]);
			}

			break;
		case SHAPE_TYPE::CUBE:

			for (int i = 0; i < cubeVertexTam; i++)
			{
				Vertex vertex;
				vertex.Position = cubePositions[i];
				vertex.Normal = cubeNormals[i];

				vertexs.push_back(vertex);
			}

			for (int i = 0; i < cubeIndexTam; i++)
			{
				indexes.push_back(cubeIndexes[i]);
			}

			break;
		default:
			return;
		}

		render->GenBuffers(VAO, VBO, EBO);
		render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
		render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);

		render->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		localVolume = new VolumeAABB();
		localVolume->Init(render);
		GenerateVolumeAABB();
	}

	void Shape::Draw()
	{
		if (IsCanDraw())
		{
			render->UseShader();
			UpdateShader();
			Entity2D::Draw();
			render->CleanShader();
		}

		Entity::Draw();
	}

	void Shape::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);
	}
}