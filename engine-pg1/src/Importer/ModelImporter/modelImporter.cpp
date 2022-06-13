#include "modelImporter.h"

namespace GL
{
	ModelImporter::ModelImporter()
	{
        meshBase = nullptr;
	}

	ModelImporter::~ModelImporter()
	{
	}

	void ModelImporter::LoadModel(Render* render, std::string path)
	{
        this->render = render;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
        this->shaderId = shaderId;

        meshBase = new Mesh();
        meshBase->Init(render, std::vector<Vertex>(), std::vector<uint>(), std::vector<Texture>());
        meshBase->SetName(scene->mRootNode->mName.C_Str());
        meshBase->SetNode(scene->mRootNode);

        if (meshBase->GetNode()->mNumChildren > 0)
        {
            meshBase->SetIsParent(true);
            meshListParent.push_back(meshBase);
        }

		ProcessNode(scene->mRootNode, scene);
	}

    Mesh* ModelImporter::GetMeshBase()
    {
        return meshBase;
    }

	void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];

            Mesh* mesh = ProcessMesh(aiMesh, scene);
            mesh->SetNode(node);
			meshList.push_back(mesh);

            for (int i = 0; i < meshListParent.size(); i++)
            {
                if (mesh->GetNode()->mParent == meshListParent[i]->GetNode())
                {
                    mesh->SetMeshParent(meshListParent[i]);
                    meshListParent[i]->AddMeshSon(mesh);
                    break;
                }
            }

            if (node->mNumChildren > 0)
            {
                if (!mesh->IsParent())
                {
                    mesh->SetIsParent(true);
                    meshListParent.push_back(mesh);
                }
            }
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh* ModelImporter::ProcessMesh(aiMesh* aiMesh, const aiScene* scene)
	{
        std::vector<Vertex> vertices;
        std::vector<uint> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;
            vector.x = aiMesh->mVertices[i].x;
            vector.y = aiMesh->mVertices[i].y;
            vector.z = aiMesh->mVertices[i].z;
            vertex.Position = vector;

            if (aiMesh->HasNormals())
            {
                vector.x = aiMesh->mNormals[i].x;
                vector.y = aiMesh->mNormals[i].y;
                vector.z = aiMesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            if (aiMesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = aiMesh->mTextureCoords[0][i].x;
                vec.y = aiMesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
        {
            aiFace face = aiMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial* material = scene->mMaterials[aiMesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        Mesh* mesh = new Mesh();
        mesh->Init(render, vertices, indices, textures);
        mesh->SetName(aiMesh->mName.C_Str());

        return mesh;
	}

	std::vector<Texture> ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
        std::vector<Texture> textures;
        uint texturesCount = mat->GetTextureCount(type);

        for (uint i = 0; i < texturesCount; i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (uint j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip)
            {
                // if texture hasn't been loaded already, load it
                std::string path = directory + '/' + str.C_Str();
                Texture texture = TextureImporter::LoadTexture(path.c_str(), true);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
	}
}