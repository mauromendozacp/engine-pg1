#include "sprite.h"
#include "StbImage/stb_image.h"

namespace GL
{
	Sprite::Sprite() : Entity2D()
	{
		uniformTexture = 0;
		textureData = nullptr;
		anim = std::vector<Animation*>();
		animIndex = 0;
		currFrame = Frame();
	}

	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		uniformTexture = 0;
		textureData = nullptr;
		anim = std::vector<Animation*>();
		animIndex = 0;
		currFrame = Frame();
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Init()
	{
		SetUniforms(render->GetTextureShaderId());

		unsigned int indexes[]
		{
			0, 1, 3,
			1, 2, 3
		};
		vertices = 6;
		vertexs = textureVertex;
		tam = sizeof(textureVertex);

		render->BindBuffer(VAO, VBO, sizeof(textureVertex), textureVertex);
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
			SetTextureCoordinates(f);
		}
	}

	void Sprite::Draw()
	{
		unsigned int shaderId = render->GetTextureShaderId();
		render->UseShaderId(shaderId);
		render->UpdateMVP(matrix.model, uniformModel, uniformView, uniformProjection);
		render->UpdateColor(color, uniformBaseColor, uniformAlpha);
		render->UpdateTexture(textureData->id, uniformTexture);

		render->Draw(VAO, VBO, EBO, vertices, tam, textureVertex);
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
			delete anim[i];
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
		SetTextureCoordinates(f);
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
		SetTextureCoordinates(f);
	}

	void Sprite::ChangeAnimation(int index)
	{
		animIndex = index;
	}

	void Sprite::SetTextureCoordinates(Frame f)
	{
		float uvCoords[]
		{
			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
			f.GetUVCords()[3].u, f.GetUVCords()[3].v
		};

		textureVertex[6] = uvCoords[0];
		textureVertex[14] = uvCoords[2];
		textureVertex[22] = uvCoords[4];
		textureVertex[30] = uvCoords[6];
		
		textureVertex[7] = uvCoords[1];
		textureVertex[15] = uvCoords[3];
		textureVertex[23] = uvCoords[5];
		textureVertex[31] = uvCoords[7];
	}

	void Sprite::SetTextureCoordinates(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
	{
		float uvCoords[]
		{
			u1, v1,
			u2, v2,
			u3, v3,
			u4, v4
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

	void Sprite::SetUniforms(uint shaderId)
	{
		Entity2D::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformTexture, "outTexture");
	}
}