#include "modelImporter.h"

namespace GL
{
	ModelImporter::ModelImporter()
	{
	}

	ModelImporter::~ModelImporter()
	{
	}

	std::vector<Mesh> ModelImporter::LoadModel(Render* render, std::string path)
	{
		Model* model = new Model(render);
		model->LoadModel(path);

		return model->GetMeshes();
	}
}