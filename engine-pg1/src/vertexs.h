#ifndef VERTEXS_H
#define VERTEXS_H

#include "GLM/glm.hpp"

namespace GL
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

#pragma region TRIANGULE_VERTEX

	const int triangVertexTam = 3;
	const int triangIndexTam = 3;
	static glm::vec3 triangPositions[triangVertexTam]
	{
		{  0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{  0.0f,  0.5f, 0.0f }
	};
	static glm::vec3 triangNormals[triangVertexTam]
	{
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	};
	static unsigned int triangIndexes[triangIndexTam]
	{
		0, 1, 2
	};

#pragma endregion

#pragma region QUAD_VERTEX

	const int quadVertexTam = 4;
	const int quadIndexTam = 6;
	static glm::vec3 quadPositions[quadVertexTam]
	{
		{ -0.5f, -0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f },
		{  0.5f,  0.5f, 0.0f },
		{ -0.5f,  0.5f, 0.0f }
	};
	static glm::vec3 quadNormals[quadVertexTam]
	{
		{ 0.0f, 1.0f, -1.0f },
		{ 0.0f, 1.0f, -1.0f },
		{ 0.0f, 1.0f, -1.0f },
		{ 0.0f, 1.0f, -1.0f }
	};
	static glm::vec2 quadTextureCoords[quadVertexTam]
	{
		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
	};
	static unsigned int quadIndexes[quadIndexTam]
	{
		0, 1, 2,
		0, 2, 3
	};

#pragma endregion

#pragma region CUBE_VERTEX

	const int cubeVertexTam = 36;
	const int cubeIndexTam = 42;
	static glm::vec3 cubePositions[cubeVertexTam]
	{
		{ -0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },

		{ -0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },

		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },

		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },

		{ -0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f, -0.5f },

		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f }
	};
	static glm::vec3 cubeNormals[cubeVertexTam]
	{
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  0.0f, -1.0f },

		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f,  1.0f },

		{ -1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },

		{  1.0f,  0.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },

		{  0.0f, -1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },

		{  0.0f,  1.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f }
	};
	static glm::vec2 cubeTextureCoords[cubeVertexTam]
	{
		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
		{ 0.0f,  0.0f },
					  
		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
		{ 0.0f,  0.0f },

		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
		{ 0.0f,  0.0f },

		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
		{ 0.0f,  0.0f },

		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
		{ 0.0f,  0.0f },

		{ 0.0f,  0.0f },
		{ 1.0f,  0.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 0.0f,  1.0f },
		{ 0.0f,  0.0f },
	};
	static unsigned int cubeIndexes[cubeIndexTam]
	{
		0,  1,  2,
		3,  4,  5,
		6,  7,  8,
		9,  10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25,	26,
		27, 28,	29,
		30, 31,	32,
		33, 34, 35
	};

#pragma endregion
}

#endif // !VERTEXS_H