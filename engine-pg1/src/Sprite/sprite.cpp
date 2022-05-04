#include "sprite.h"
#include "StbImage/stb_image.h"

namespace GL
{
	Sprite::Sprite() : Entity2D()
	{
		type = SPRITE_TYPE::QUAD;
		textureData = nullptr;
		uniformTexture = 0;
		animIndex = 0;
		anim = std::vector<Animation*>();
		currFrame = Frame();
		transparent = false;
	}

	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		type = SPRITE_TYPE::QUAD;
		textureData = nullptr;
		uniformTexture = 0;
		animIndex = 0;
		anim = std::vector<Animation*>();
		currFrame = Frame();
		transparent = false;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Init(SPRITE_TYPE type)
	{
		this->type = type;

		shaderId = render->GetTextureShaderId();
		SetUniforms(shaderId);

		uint* indexes = 0;

		switch (type)
		{
		case GL::SPRITE_TYPE::QUAD:
			indexes = quadIndexes;
			vertices = quadIndexTam;
			vertexs = quadVertex;
			tam = sizeof(vertexs) * quadVertTam;

			break;
		case GL::SPRITE_TYPE::CUBE:
			indexes = cubeIndexes;
			vertices = cubeIndexTam;
			vertexs = cubeVertex;
			tam = sizeof(vertexs) * cubeVertTam;

			break;
		default:
			break;
		}

		render->GenBuffers(VAO, VBO, EBO, UVB);
		render->BindBuffer(VAO, VBO, tam, vertexs);
		render->BindIndexs(EBO, sizeof(indexes) * vertices, indexes);
		
		render->SetBaseAttribs(locationPosition, 3, 6 * sizeof(float), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		SetTextureCoordinates(currFrame);
		render->SetTextureAttribs(locationTexCoord, 2, 2, 0);
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
		render->BlendEnable();
		render->UseShader(shaderId);
		UpdateShader();
		render->UpdateTexture(uniformTexture, textureData->id);
		render->BindDiffuseMap(textureData->id);
		render->BindSpecularMap(textureData->id);
		Entity2D::Draw();
		render->TextureDisable();
		render->CleanShader();
		render->BlendDisable();
	}

	void Sprite::DeInit()
	{
		render->UnBind(VAO, VBO, EBO, UVB);
		render->TextureDelete(uniformTexture, textureData->id);

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

	void Sprite::SetTexture(Texture* texture)
	{
		textureData = texture;
	}

	void Sprite::LoadTexture(const char* path, bool invertImage)
	{
		textureData = new Texture(TextureImporter::LoadTexture(path, invertImage));
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
		float quadCoords[8] =
		{
			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
			f.GetUVCords()[3].u, f.GetUVCords()[3].v
		};

		switch (type)
		{
		case GL::SPRITE_TYPE::QUAD:
			render->BindUV(UVB, sizeof(quadCoords), quadCoords);

			break;
		case GL::SPRITE_TYPE::CUBE:
			float cubeCoords[72] =
			{
				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1],

				quadCoords[0], quadCoords[1],
				quadCoords[2], quadCoords[3],
				quadCoords[4], quadCoords[5],
				quadCoords[4], quadCoords[5],
				quadCoords[6], quadCoords[7],
				quadCoords[0], quadCoords[1]
			};

			render->BindUV(UVB, sizeof(cubeCoords), cubeCoords);
			break;
		}
	}

	void Sprite::SetTransparent(bool tranparent)
	{
		this->transparent = tranparent;
	}

	bool Sprite::GetTransparent()
	{
		return transparent;
	}

	void Sprite::SetUniforms(uint shaderId)
	{
		Entity2D::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformTexture, "ourTexture");
	}
}