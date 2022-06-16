#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include "exports.h"

#include "Entity/Entity3D/entity3D.h"

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

		static Entity3D* LoadModel(Render* rend, std::string path);

	private:
		static Render* render;
		static std::string directory;
		static std::vector<Texture> textures_loaded;

		static void ProcessNode(Entity3D* parent, aiNode* node, const aiScene* scene);
		static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}

#endif // !MODEL_IMPORTER_H