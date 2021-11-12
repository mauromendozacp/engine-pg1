#ifndef TILEMAP_H
#define TILEMAP_H

#include "exports.h"
#include <vector>
#include "Tile/tile.h"

namespace GL
{
	class GRAPHICSENGINE_API Tilemap
	{
	public:
		Tilemap();
		~Tilemap();

		Tile GetTile(unsigned int id);
		void SetTile(Tile tile);
		void SetMapTileId(int layer, unsigned int col, unsigned int row, unsigned int id);

		void SetTileDimentions(float tileWidth, float tileHeight);
		void SetDimentions(float width, float height);

	private:
		std::vector<Tile> tiles;
		std::vector<Tile**> grid;

		unsigned int width;
		unsigned int height;

		float tileWidth;
		float tileHeight;

		//Texture texture;

		float imageWidth;
		float imageHeight;
	};
}

#endif // !TILEMAP_H