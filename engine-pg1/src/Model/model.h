#ifndef MODEL_H
#define MODEL_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "Mesh/mesh.h"
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace GL
{
	class GRAPHICSENGINE_API Model
	{
	public:
		Model(Render* render);
		~Model();

		void LoadModel(std::string const& path);
		void Draw();

	private:
		Render* render;
		std::vector<Mesh> meshes;
		std::vector<Texture> textures_loaded;
		std::string directory;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}

#endif // !MODEL_H