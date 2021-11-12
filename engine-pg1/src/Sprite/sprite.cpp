#include "sprite.h"
#include "StbImage/stb_image.h"

namespace GL
{
	const int textureVertTam = 32;
	static float textureVertex[textureVertTam]
	{
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
	};

	Sprite::Sprite() : Entity2D()
	{
		textureId = 0;
		anim = NULL;
		height = 0;
		width = 0;
	}

	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		textureId = 0;
		anim = NULL;
		height = 0;
		width = 0;
	}

	Sprite::~Sprite()
	{
		glDeleteTextures(1, &textureId);

		if (anim != NULL)
		{
			delete anim;
			anim = NULL;
		}
	}

	void Sprite::Init(std::string path)
	{
		unsigned int indexes[]
		{
			0, 1, 3,
			1, 2, 3
		};
		vertices = 6;
		vertexs = textureVertex;
		tam = sizeof(textureVertex);

		render->BindBuffer(VAO, VBO, tam, vertexs);
		render->BindIndexs(EBO, sizeof(indexes), indexes);
		BindAttrib();
		LoadTexture(path);

		anim = new Animation();
	}

	void Sprite::Update(float timer)
	{
		if (!anim)
			return;

		anim->Update(timer);

		int currFrame = anim->GetCurrentFrame();
		if (currFrame != 0)
		{
			Frame f = anim->GetFrames()[currFrame];

			float uvCoords[]
			{
				f.GetUVCords()[0].u, f.GetUVCords()[0].v,
				f.GetUVCords()[1].u, f.GetUVCords()[1].v,
				f.GetUVCords()[2].u, f.GetUVCords()[2].v,
				f.GetUVCords()[3].u, f.GetUVCords()[3].v
			};

			vertexs[6]  = uvCoords[0];
			vertexs[14] = uvCoords[2];
			vertexs[22] = uvCoords[4];
			vertexs[30] = uvCoords[6];

			vertexs[7]	= uvCoords[1];
			vertexs[15] = uvCoords[3];
			vertexs[23] = uvCoords[5];
			vertexs[31] = uvCoords[7];

			/*render->BindTextureBuffer(VBO, sizeof(uvCoords), uvCoords);
			BindAttrib();*/
		}
	}

	void Sprite::Draw()
	{
		unsigned int shaderId = render->GetTextureShaderId();
		render->UseShaderId(shaderId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		SetShader(shaderId);
		Entity::Draw(shaderId);
	}

	void Sprite::AddAnimation(int rows, int cols, float duration)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				anim->AddFrame(i, j, width / cols, height / rows, width, height, duration, 10);
			}
		}
	}

	void Sprite::LoadTexture(std::string path)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		int nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			int channelType = GL_RGB;
			switch (nrChannels)
			{
			case 1:
				channelType = GL_R;
				break;
			case 2:
				channelType = GL_RG;
				break;
			case 3:
				channelType = GL_RGB;
				break;
			case 4:
				channelType = GL_RGBA;
				break;
			default:
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, channelType, width, height, 0, channelType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	void Sprite::SetShader(unsigned int shaderId)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shaderId, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shaderId, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		unsigned int textureLoc = glGetUniformLocation(shaderId, "ourTexture");
		glUniform1f(textureLoc, textureId);
	}

	void Sprite::BindAttrib()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}
}