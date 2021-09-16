#ifndef ENTITY_H
#define ENTITY_H

#include "exports.h"
#include "Renderer/renderer.h"

namespace GL
{
	class GRAPHICSENGINE_API Entity
	{
	private:
		Render* render;
		

	public:
		Entity();
		~Entity();
	};

	
}

#endif // !ENTITY_H