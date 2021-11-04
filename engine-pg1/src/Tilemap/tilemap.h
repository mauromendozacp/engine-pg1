#ifndef TILEMAP_H
#define TILEMAP_H

#include "exports.h"
#include "Sprite/sprite.h"

namespace GL
{
	class GRAPHICSENGINE_API Tilemap : Sprite
	{
	public:
		Tilemap(Render* render);
		~Tilemap();

	private:

	};
}

#endif // !TILEMAP_H