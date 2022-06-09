#include "sprite.h"

namespace GL
{
	Sprite::Sprite() : Entity2D()
	{
		type = SPRITE_TYPE::QUAD;
		baseTexture = nullptr;
		uniformBaseTexture = 0;
		animIndex = 0;
		anim = std::vector<Animation*>();
		currFrame = Frame();
		transparent = false;
	}

	Sprite::Sprite(Render* render) : Entity2D(render)
	{
		type = SPRITE_TYPE::QUAD;
		baseTexture = nullptr;
		uniformBaseTexture = 0;
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
		render->UpdateTexture(uniformBaseTexture, baseTexture->id);
		render->BindDiffuseMap(baseTexture->id);
		render->BindSpecularMap(baseTexture->id);
		Entity2D::Draw();
		render->TextureDisable();
		render->CleanShader();
		render->BlendDisable();
	}

	void Sprite::DeInit()
	{
		render->UnBind(VAO, VBO, EBO, UVB);
		render->TextureDelete(uniformBaseTexture, baseTexture->id);

		if (baseTexture != nullptr)
		{
			delete baseTexture;
			baseTexture = nullptr;
		}

		for (int i = 0; i < anim.size(); i++)
		{
			delete anim[i];
		}
	}

	void Sprite::SetTexture(Texture* texture, TEXTURE_TYPE type)
	{
		switch (type)
		{
		case TEXTURE_TYPE::BASE:
			baseTexture = texture;
			break;
		case TEXTURE_TYPE::DIFFUSE:
			if (material != nullptr)
			{
				((TextureMaterial*)material)->SetDiffuse(texture->id);
			}
			break;
		case TEXTURE_TYPE::SPECULAR:
			if (material != nullptr)
			{
				((TextureMaterial*)material)->SetSpecular(texture->id);
			}
			break;
		default:
			baseTexture = nullptr;
			break;
		}
	}

	void Sprite::LoadTexture(const char* path, bool invertImage, TEXTURE_TYPE type)
	{
		SetTexture(new Texture(TextureImporter::LoadTexture(path, invertImage)), type);
		animIndex = 0;
	}

	void Sprite::AddAnimation(AtlasConfig atlas, float speed)
	{
		Animation* a = new Animation();
		a->SetAnimation(baseTexture, speed);
		a->AddFrames(atlas);
		anim.push_back(a);

		Frame f = anim[animIndex]->GetFrames()[0];
		SetTextureCoordinates(f);
	}

	void Sprite::AddAnimation(int rows, int cols, float speed)
	{
		Animation* a = new Animation();
		a->SetAnimation(baseTexture, speed);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				a->AddFrame(i, j, baseTexture->width / cols, baseTexture->height / rows, rows * cols);
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
		render->SetUniform(shaderId, uniformBaseTexture, "ourTexture");
	}
}