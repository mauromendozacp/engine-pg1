#include "model.h"

namespace GL
{
	Model::Model(Render* render)
	{
		this->render = render;
	}

	Model::~Model()
	{
	}

	void Model::LoadModel(char* path)
	{
		
	}

	void Model::Draw()
	{
		for (uint i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}
	}
}