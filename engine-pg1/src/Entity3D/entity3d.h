#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"

namespace GL
{
	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D();
		Entity3D(Render* render);
		~Entity3D();

	private:

	};
}

#endif // !ENTITY3D_H