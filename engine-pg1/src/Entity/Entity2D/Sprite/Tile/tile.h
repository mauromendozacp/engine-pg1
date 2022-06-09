#ifndef TILE_H
#define TILE_H

#include "exports.h"
#include "../sprite.h"

namespace GL
{
	class GRAPHICSENGINE_API Tile : public Sprite
	{
	public:
		Tile();
		Tile(Render* render);
		~Tile();

		unsigned int GetId();
		void SetId(unsigned int id);

		bool IsWalkeable();
		void SetWalkeable(bool walkeable);

		void SetRender(Render* render);

	private:
		unsigned int id;
		bool isWalkeable;
	};
}

#endif // !TILE_H
