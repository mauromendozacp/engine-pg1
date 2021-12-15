#include "sprite.h"
#include "StbImage/stb_image.h"

namespace GL
{
	Sprite::Sprite() : Entity2D()
	{
		textureData = nullptr;
		anim = std::vector<Animation*>();
		animIndex = 0;
	}

	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		textureData = nullptr;
		anim = std::vector<Animation*>();
		animIndex = 0;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Init()
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
		render->BindExtraAttrib();
	}

	void Sprite::Update()
	{
		if (anim.size() == 0)
			return;

		if (anim[animIndex]->Update())
		{
			Frame f = anim[animIndex]->GetFrames()[anim[animIndex]->GetCurrentFrame()];
			BindTexture(f);
		}
	}

	void Sprite::Draw()
	{
		unsigned int shaderId = render->GetTextureShaderId();
		render->UseShaderId(shaderId);
		Update();
		render->SetShader(shaderId, color, textureData->id);
		Entity::Draw(shaderId);
	}

	void Sprite::DeInit()
	{
		glDeleteTextures(1, &textureData->id);

		if (textureData != nullptr)
		{
			delete textureData;
			textureData = nullptr;
		}

		for (int i = 0; i < anim.size(); i++)
		{
			delete[] anim[i];
		}
	}

	void Sprite::SetTexture(TextureData* texture)
	{
		textureData = texture;
	}

	void Sprite::LoadTexture(const char* path, bool invertImage)
	{
		textureData = new TextureData(TextureImporter::LoadTexture(path, invertImage));
		animIndex = 0;
	}

	void Sprite::AddAnimation(AtlasConfig atlas, float speed)
	{
		Animation* a = new Animation();
		a->SetAnimation(textureData, speed);
		a->AddFrames(atlas);
		anim.push_back(a);

		Frame f = anim[animIndex]->GetFrames()[0];
		BindTexture(f);
	}

	void Sprite::AddAnimation(int rows, int cols, float speed)
	{
		Animation* a = new Animation();
		a->SetAnimation(textureData, speed);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				a->AddFrame(i, j, textureData->width / cols, textureData->height / rows, rows * cols);
			}
		}
		anim.push_back(a);

		Frame f = anim[animIndex]->GetFrames()[0];
		BindTexture(f);
	}

	void Sprite::ChangeAnimation(int index)
	{
		animIndex = index;
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