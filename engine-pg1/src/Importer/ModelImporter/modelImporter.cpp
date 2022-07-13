#include "modelImporter.h"

namespace GL
{
    Render* ModelImporter::render = nullptr;
    std::vector<Texture> ModelImporter::textures_loaded = std::vector<Texture>();
    std::string ModelImporter::directory = std::string();
    std::string assimpfbx = "$AssimpFbx$";

	ModelImporter::ModelImporter()
	{
	}

	ModelImporter::~ModelImporter()
	{
	}

    Entity3D* ModelImporter::LoadModel(Render* rend, std::string path)
	{
        render = rend;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return nullptr;
		}
		directory = path.substr(0, path.find_last_of('/'));
        textures_loaded.clear();

        Entity3D* model = new Entity3D(render);
        model->Init();
        model->SetName(scene->mRootNode->mName.C_Str());

        ProcessNode(model, scene->mRootNode, scene);

        return model;
	}

    void ModelImporter::ProcessNode(Entity3D* parent, aiNode* node, const aiScene* scene)
	{
        Entity3D* entityNode = nullptr;
        std::string name = node->mName.C_Str();

        if (node->mNumMeshes > 0)
        {
            std::vector<Mesh*> meshes = std::vector<Mesh*>();
            for (uint i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(ProcessMesh(aiMesh, scene));
            }

            entityNode = new Entity3D(meshes, render);
        }
        else
        {
            entityNode = new Entity3D(render);
        }

        for (uint i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(entityNode, node->mChildren[i], scene);
        }

        parent->AddNode(entityNode);
        entityNode->SetName(name);
        entityNode->SetParent(parent);

        entityNode->Init();
	}

    Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<uint> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> baseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "base_color");
        textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        std::vector<Texture> metalnessMaps = LoadMaterialTextures(material, aiTextureType_METALNESS, "metalness");
        textures.insert(textures.end(), metalnessMaps.begin(), metalnessMaps.end());
        std::vector<Texture> diffuseRoughnessMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "diffuse_roughness");
        textures.insert(textures.end(), diffuseRoughnessMaps.begin(), diffuseRoughnessMaps.end());
        std::vector<Texture> ambientOcclusionMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "ambient_occlusion");
        textures.insert(textures.end(), ambientOcclusionMaps.begin(), ambientOcclusionMaps.end());

        aiColor4D color(0.f, 0.f, 0.f, 0.f);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);

        Material* mat = nullptr;
        if (textures.size() > 0)
        {
            mat = MaterialManager::GetTextureMaterial();
        }
        else
        {
            mat = MaterialManager::GetSolidMaterial();
        }

        Mesh* m = new Mesh(render, vertices, indices, textures);
        m->color = Color(color.r, color.g, color.b);
        m->material = mat;

        return m;
    }

	std::vector<Texture> ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
        std::vector<Texture> textures;
        uint texturesCount = mat->GetTextureCount(type);

        for (uint i = 0; i < texturesCount; i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for (uint j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {
                std::string path = directory + '/' + str.C_Str();
                Texture texture = TextureImporter::LoadTexture(path.c_str(), true);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
	}
}