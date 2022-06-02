#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "Mesh/mesh.h"
#include <vector>
#include <string>

namespace GL
{
	class Entity3D
	{
	public:
		Entity3D(Render* render);
		~Entity3D();

		void Init(std::string path);
		void Draw();

	private:
		std::vector<Mesh> meshes;
	};
}

#endif // !ENTITY3D_H