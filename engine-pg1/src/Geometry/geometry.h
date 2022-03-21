#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Entity3D/entity3d.h"

namespace GL
{
	enum class GEOMETRY_TYPE
	{
		CUBE,
		SPHERE,
		CAPSULE
	};

	class GRAPHICSENGINE_API Geometry : public Entity3D
	{
	public:
		Geometry();
		Geometry(Render* render);
		~Geometry();

		void Init(GEOMETRY_TYPE geometryType);
		void Draw();

	private:

	};
}

#endif // !GEOMETRY_H
