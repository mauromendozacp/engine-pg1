#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"
#include "Mesh/mesh.h"

#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D();
		Entity3D(Render* render);
		Entity3D(std::vector<Mesh*> meshes, Render* render);
		~Entity3D();

		void Init();
		void Draw();
		void DeInit();

		void CanDrawVolume(bool status);
		bool IsCanDrawVolume();

		glm::vec3 minAABB;
		glm::vec3 maxAABB;

		void GenerateVolumeAABB() override;

	protected:
		std::vector<Mesh*> meshes;

		uint uniformAffectedLight;

		bool affectedLight;
		bool drawVolume;

		virtual void SetUniforms() override;
		virtual void UpdateShader() override;
	};
}

#endif // !ENTITY3D_H