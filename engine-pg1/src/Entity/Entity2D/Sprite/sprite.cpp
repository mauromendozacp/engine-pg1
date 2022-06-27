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
		useTexture = true;

		SetUniforms();

		switch (type)
		{
		case GL::SPRITE_TYPE::QUAD:
			for (int i = 0; i < quadVertexTam; i++)
			{
				Vertex vertex;
				vertex.Position = quadPositions[i];
				vertex.Normal = quadNormals[i];
				vertex.TexCoords = quadTextureCoords[i];

				vertexs.push_back(vertex);
			}

			for (int i = 0; i < quadIndexTam; i++)
			{
				indexes.push_back(quadIndexes[i]);
			}

			break;
		case GL::SPRITE_TYPE::CUBE:

			for (int i = 0; i < cubeVertexTam; i++)
			{
				Vertex vertex;
				vertex.Position = cubePositions[i];
				vertex.Normal = cubeNormals[i];
				vertex.TexCoords = cubeTextureCoords[i];

				vertexs.push_back(vertex);
			}

			for (int i = 0; i < cubeIndexTam; i++)
			{
				indexes.push_back(cubeIndexes[i]);
			}

			break;
		default:
			break;
		}

		render->GenBuffers(VAO, VBO, EBO, UVB);
		render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
		render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);

		render->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		//SetTextureCoordinates(currFrame);
		render->SetBaseAttribs(locationTexCoord, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		GenerateVolumeAABB();
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
		render->UseShader();
		render->BlendEnable();

		UpdateShader();
		render->UseTexture(0, baseTexture->id);
		Entity2D::Draw();

		render->CleanTexture();
		render->TextureDisable();
		render->BlendDisable();
		render->CleanShader();
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

	void Sprite::SetUniforms()
	{
		Entity2D::SetUniforms();
		render->SetUniform(uniformBaseTexture, "baseTexture");
	}

	void Sprite::UpdateShader()
	{
		Entity2D::UpdateShader();
		render->UpdateTexture(uniformBaseTexture, baseTexture->id);
	}
}