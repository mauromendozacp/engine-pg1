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
		//X		Y	  Z		 R	   G	 B
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
		//X		Y	  Z		 R	   G	 B
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   // bottom right
		-0.5f,  0.5f, 0.0f,	  1.0f, 1.0f, 1.0f,	  // top left
	};

#pragma endregion

	#pragma region CUBE_VERTEX

	const int cubeVertTam = 48;
	const int cubeIndexTam = 42;
	static unsigned int cubeIndexes[cubeIndexTam] = {
		0, 1, 2,
		2, 3, 0,
		3, 2, 0,
		2, 1, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3
	};
	static float cubeVertex[cubeVertTam]
	{
		// positions         // colors
		//X		Y	  Z		 R	   G	 B
		-1.0, -1.0,  1.0,	1.0f, 1.0f, 1.0f,   // top right
		 1.0, -1.0,  1.0,	1.0f, 1.0f, 1.0f,   // bottom right
		 1.0,  1.0,  1.0,	1.0f, 1.0f, 1.0f,   // bottom right
		-1.0,  1.0,  1.0,	1.0f, 1.0f, 1.0f,	// top left
		-1.0, -1.0, -1.0,	1.0f, 1.0f, 1.0f,   // top right
		 1.0, -1.0, -1.0,	1.0f, 1.0f, 1.0f,   // bottom right
		 1.0,  1.0, -1.0,	1.0f, 1.0f, 1.0f,   // bottom right
		-1.0,  1.0, -1.0,	1.0f, 1.0f, 1.0f,	// top left
	};

	#pragma endregion
}