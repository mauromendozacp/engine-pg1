#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include "exports.h"

#include "Mesh/mesh.h"
#include "StbImage/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API ModelImporter
	{
	public:
		ModelImporter();
		~ModelImporter();

		void LoadModel(Render* render, std::string path);
		Mesh* GetMeshBase();

	private:
		Render* render;
		std::vector<Mesh*> meshList;
		std::vector<Mesh*> meshListParent;
		Mesh* meshBase;
		uint shaderId;

		std::vector<Texture> textures_loaded;
		std::string directory;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}

#endif // !MODEL_IMPORTER_H