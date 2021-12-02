#include "sprite.h"
#include "StbImage/stb_image.h"

namespace GL
{
	Sprite::Sprite() : Entity2D()
	{
		textureData = nullptr;
		anim = nullptr;
	}

	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		textureData = nullptr;
		anim = nullptr;
	}

	Sprite::~Sprite()
	{
		glDeleteTextures(1, &textureData->id);

		if (textureData != nullptr)
		{
			delete textureData;
			textureData = nullptr;
		}
		if (anim != nullptr)
		{
			delete anim;
			anim = nullptr;
		}
	}

	void Sprite::Init(const char* path, bool invertImage)
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
		textureData = new TextureData(TextureImporter::LoadTexture(path, invertImage));

		anim = new Animation();
	}

	void Sprite::Update()
	{
		if (!anim)
			return;

		if (anim->Update())
		{
			Frame f = anim->GetFrames()[anim->GetCurrentFrame()];
			BindTexture(f);
		}
	}

	void Sprite::Draw()
	{
		unsigned int shaderId = render->GetTextureShaderId();
		render->UseShaderId(shaderId);
		Update();
		glBindTexture(GL_TEXTURE_2D, textureData->id);
		SetShader(textureData->id);
		Entity::Draw(shaderId);
	}

	void Sprite::AddAnimation(AtlasConfig atlas, float speed)
	{
		anim->SetAnimation(textureData, speed);
		anim->AddFrames(atlas);

		Frame f = anim->GetFrames()[0];
		BindTexture(f);
	}

	void Sprite::AddAnimation(int rows, int cols, float speed)
	{
		anim->SetAnimation(textureData, speed);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				anim->AddFrame(i, j, textureData->width / cols, textureData->height / rows, rows * cols);
				//anim->AddFrame(i, j, textureData->width / cols, textureData->height / rows, duration, 10);
			}
		}

		Frame f = anim->GetFrames()[0];
		BindTexture(f);
	}

	void Sprite::SetShader(unsigned int shaderId)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shaderId, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shaderId, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		unsigned int textureLoc = glGetUniformLocation(shaderId, "ourTexture");
		glUniform1f(textureLoc, (GLfloat)textureData->id);
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

	void Sprite::BindTexture(Frame f)
	{
		float uvCoords[]
		{
			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
			f.GetUVCords()[3].u, f.GetUVCords()[3].v
		};

		vertexs[6] = uvCoords[0];
		vertexs[14] = uvCoords[2];
		vertexs[22] = uvCoords[4];
		vertexs[30] = uvCoords[6];

		vertexs[7] = uvCoords[1];
		vertexs[15] = uvCoords[3];
		vertexs[23] = uvCoords[5];
		vertexs[31] = uvCoords[7];
	}
}