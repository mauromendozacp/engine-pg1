#ifndef TILE_H
#define TILE_H

#include "exports.h"
#include "Sprite/sprite.h"

namespace GL
{
	class GRAPHICSENGINE_API Tile : Sprite
	{
	public:
		Tile();
		Tile(Render* render);
		~Tile();

		unsigned int GetId();
		void SetId(unsigned int id);

		bool IsWalkeable();
		void SetWalkeable(bool walkeable);

	private:
		unsigned int id;
		bool isWalkeable;
	};
}

#endif // !TILE_H
