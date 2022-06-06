#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "exports.h"
#include "Entity/entity.h"
#include <Material/material.h>
#include "Importer/ModelImporter/modelImporter.h"
#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D(Render* render);
		~Entity3D();

		void Init(std::string path);
		void Draw();

		Material* material;

	private:
		std::vector<Mesh> meshes;

		uint uniformAffectedLight;

		bool affectedLight;

		void SetUniforms(uint shaderId);
		void UpdateShader();
	};
}

#endif // !ENTITY3D_H