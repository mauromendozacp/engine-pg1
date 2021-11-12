#include "tilemap.h"

namespace GL
{
	Tilemap::Tilemap()
	{
		tiles = std::vector<Tile>();
		grid = std::vector<Tile**>();

		width = 0;
		height = 0;

		tileWidth = 0.0f;
		tileHeight = 0.0f;

		//texture;

		imageWidth = 0.0f;
		imageHeight = 0.0f;
	}

	Tilemap::~Tilemap()
	{
	}

	Tile Tilemap::GetTile(unsigned int id)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (id == tiles[i].GetId())
			{
				return tiles[i];
			}
		}

		return NULL;
	}

	void Tilemap::SetTile(Tile tile)
	{
		tiles.push_back(tile);
	}

	void Tilemap::SetMapTileId(int layer, unsigned int col, unsigned int row, unsigned int id)
	{
		grid[layer][col][row] = GetTile(id);
	}

	void Tilemap::SetTileDimentions(float tileWidth, float tileHeight)
	{
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
	}

	void Tilemap::SetDimentions(float width, float height)
	{
		this->width = width;
		this->height = height;

		Tile** tileMap;
		tileMap = new Tile * [height];
		for (int i = 0; i < height; i++) {
			tileMap[i] = new Tile[width];
		}
		grid.push_back(tileMap);
	}
}