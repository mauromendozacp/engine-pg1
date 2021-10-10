#include "sprite.h"

namespace GL
{
	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		textureId = 0;
	}

	Sprite::~Sprite()
	{
		glDeleteTextures(1, &textureId);
	}

	void Sprite::Init(std::string path)
	{
		float vertex[]
		{
			//positions				//colors				//texture
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // bottom right
			 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // bottom left
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // top right
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // top left
		};
		unsigned int indexes[]
		{
			0, 1, 3,
			1, 2, 3
		};
		vertices = 6;

		render->BindBuffer(VAO, VBO, sizeof(vertex) * 18, vertex);
		render->BindIndexs(EBO, sizeof(indexes) * 3, indexes);
		BindAttrib();
		LoadTexture(path);
	}

	void Sprite::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		//Entity::Draw();
	}

	void Sprite::LoadTexture(std::string path)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Sprite::BindAttrib()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}
}