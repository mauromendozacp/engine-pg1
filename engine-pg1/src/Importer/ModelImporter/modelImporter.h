#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include "exports.h"
#include "Model/model.h"
#include "Mesh/mesh.h"
#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API ModelImporter
	{
	public:
		ModelImporter();
		~ModelImporter();

		static std::vector<Mesh> LoadModel(Render* render, std::string path);
	};
}

#endif // !MODEL_IMPORTER_H