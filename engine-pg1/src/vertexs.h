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
	const int cubeIndexTam = 36;
	static unsigned int cubeIndexes[cubeIndexTam] = {
		0, 1, 2,
		2, 3, 0,
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
		-0.5, -0.5,  0.5,	1.0f, 1.0f, 1.0f,   // near top right
		 0.5, -0.5,  0.5,	1.0f, 1.0f, 1.0f,   // near bottom right
		 0.5,  0.5,  0.5,	1.0f, 1.0f, 1.0f,   // near bottom right
		-0.5,  0.5,  0.5,	1.0f, 1.0f, 1.0f,	// near top left
		-0.5, -0.5, -0.5,	1.0f, 1.0f, 1.0f,   // far top right
		 0.5, -0.5, -0.5,	1.0f, 1.0f, 1.0f,   // far bottom right
		 0.5,  0.5, -0.5,	1.0f, 1.0f, 1.0f,   // far bottom right
		-0.5,  0.5, -0.5,	1.0f, 1.0f, 1.0f,	// far top left
	};

	#pragma endregion

	#pragma region CUBE3D_VERTEX

	const int cube3dVertTam = 144;
	const int cube3dIndexTam = 42;
	static unsigned int cube3dIndexes[cube3dIndexTam]
	{
		0, 1, 3, // FRONT
		1, 2, 3,

		4, 5, 7, // BACK
		5, 6, 7,

		8, 9, 11, // LEFT
		9, 10, 11,

		12, 13, 15, // BOTTOM
		13, 14, 15,

		16, 17, 19, // RIGHT 
		17, 18, 19,

		20, 21, 23, // TOP
		21, 22, 23
	};
	static float cube3dVertex[cube3dVertTam]
	{
		//far
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,

		//near
		 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,

		//left
		-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,

		//right
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,

		 //top
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,

		 //bottom
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
	};

	#pragma endregion
}