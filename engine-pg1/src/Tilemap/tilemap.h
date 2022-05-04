#ifndef TILEMAP_H
#define TILEMAP_H

#include "exports.h"
#include <vector>
#include "Tile/tile.h"
#include "Tinyxml2/tinyxml2.h"
#include "Collision/collision.h"

namespace GL
{
	class GRAPHICSENGINE_API Tilemap
	{
	public:
		Tilemap();
		Tilemap(Render* render);
		~Tilemap();

		const Tile& GetTile(unsigned int id);
		void SetTile(Tile tile);
		void SetMapTileId(int layer, unsigned int col, unsigned int row, unsigned int id);

		bool ImportTileMap(std::string filePath, std::string imagePath);
		void SetTileDimentions(float tileWidth, float tileHeight);
		void SetDimentions(float width, float height);
		void SetSize(float size);
		void CheckCollision(Entity2D* entity);

		void Draw();
		void DeInit();

	private:
		Render* render;

		std::vector<Tile> tiles;
		std::vector<Tile**> grid;

		unsigned int width;
		unsigned int height;

		float tileWidth;
		float tileHeight;

		Texture texture;

		float imageWidth;
		float imageHeight;
	};
}

#endif // !TILEMAP_H