#include "mesh.h"

namespace GL
{
	Mesh::Mesh()
	{
		render = nullptr;

		material = nullptr;
		color = Color();

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();
		textures = std::vector<Texture>();

		VAO = 0;
		VBO = 0;
		EBO = 0;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformBaseTexture = 0;
		uniformUseTexture = 0;

		locationPosition = 0;
		locationNormal = 0;
		locationTexCoord = 0;
	}

	Mesh::Mesh(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures)
	{
		this->render = render;

		material = nullptr;
		color = Color();

		this->vertexs = vertexs;
		this->indexes = indexes;
		this->textures = textures;

		VAO = 0;
		VBO = 0;
		EBO = 0;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformBaseTexture = 0;
		uniformUseTexture = 0;

		locationPosition = 0;
		locationNormal = 0;
		locationTexCoord = 0;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Init()
	{
		SetUniforms();

		render->GenBuffers(VAO, VBO, EBO);
		if (vertexs.size() == 0)
		{
			render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), 0);
		}
		else
		{
			render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
		}

		if (indexes.size() == 0)
		{
			render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), 0);
		}
		else
		{
			render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);
		}

		render->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		render->SetBaseAttribs(locationTexCoord, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		SolidMaterial* defaultSolidMaterial = new SolidMaterial(render);
		defaultSolidMaterial->Init();
		defaultSolidMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultSolidMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		defaultSolidMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		defaultSolidMaterial->SetShininess(64.f);

		material = defaultSolidMaterial;
	}

	void Mesh::Draw()
	{
		render->UseShader();
		render->BlendEnable();
		render->TextureEnable();

		for (int i = 0; i < textures.size(); i++)
		{
			render->UseTexture(i, textures[i].id);
		}

		UpdateShader();

		render->Draw(VAO, indexes.size());

		render->CleanTexture();
		render->TextureDisable();
		render->BlendDisable();
		render->CleanShader();
	}

	void Mesh::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);

		if (textures.size() > 0)
		{
			//render->TextureDelete(uniformBaseTexture, mesh.textures[0].id);
		}

		vertexs.clear();
		indexes.clear();
		textures.clear();
	}

	std::vector<Vertex> Mesh::GetVertexs()
	{
		return vertexs;
	}

	void Mesh::SetUniforms()
	{
		render->SetUniform(uniformColor, "color");
		render->SetUniform(uniformAlpha, "a");
		render->SetUniform(uniformBaseTexture, "baseTexture");
		render->SetUniform(uniformUseTexture, "useTexture");

		render->SetLocation(locationPosition, "aPos");
		render->SetLocation(locationNormal, "aNor");
		render->SetLocation(locationTexCoord, "aTex");
	}

	void Mesh::UpdateShader()
	{
		render->UpdateStatus(uniformUseTexture, textures.size() > 0);
		if (textures.size() > 0)
		{
			render->UpdateTexture(uniformBaseTexture, textures[0].id);
		}

		if (material != nullptr)
		{
			material->UpdateShader();
		}
		render->UpdateColor(uniformColor, uniformAlpha, color.GetColor());
	}
}