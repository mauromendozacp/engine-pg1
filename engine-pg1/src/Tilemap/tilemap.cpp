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

		texture = TextureData();

		imageWidth = 0.0f;
		imageHeight = 0.0f;
	}

	Tilemap::Tilemap(Render* render)
	{
		this->render = render;

		tiles = std::vector<Tile>();
		grid = std::vector<Tile**>();

		width = 0;
		height = 0;

		tileWidth = 0.0f;
		tileHeight = 0.0f;

		texture = TextureData();

		imageWidth = 0.0f;
		imageHeight = 0.0f;
	}

	Tilemap::~Tilemap()
	{
	}

	const Tile& Tilemap::GetTile(unsigned int id)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (id == tiles[i].GetId())
			{
				return tiles[i];
			}
		}

		return nullptr;
	}

	void Tilemap::SetTile(Tile tile)
	{
		tiles.push_back(tile);
	}

	void Tilemap::SetMapTileId(int layer, unsigned int col, unsigned int row, unsigned int id)
	{
		grid[layer][col][row] = GetTile(id);
	}

	bool Tilemap::ImportTileMap(std::string filePath, std::string imagePath)
	{
		tinyxml2::XMLDocument doc; //guarda el documento
		tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

		errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
		if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED)
			return false;

		// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
		tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
		if (mapNode == nullptr)
			return false;

		SetDimentions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
		SetTileDimentions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles

		// Loading Tilset element
		tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
		if (pTileset == NULL)
			return false;

		int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
		int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
		int rows = tileCount / columns;

		texture = TextureImporter::LoadTexture(imagePath.c_str(), true);
		pTileset->FirstChildElement("image")->Attribute("source");// Loading Textures

		// Save the Tiles in the TileMap
		imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
		imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");

		float tileX = 0.0f, tileY = 0.0f;
		int _id = 1;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Tile newTile;

				newTile.Init(SPRITE_TYPE::QUAD);
				newTile.SetId(_id);
				newTile.SetRender(render);
				newTile.LoadTexture(imagePath.c_str(), false);
				newTile.SetScale(tileWidth, tileHeight, 1.f);

				Frame frame;
				frame.GetUVCords()[0].u = (tileX + tileWidth) / imageWidth;
				frame.GetUVCords()[0].v = tileY / imageHeight;
				frame.GetUVCords()[1].u = (tileX + tileWidth) / imageWidth; 
				frame.GetUVCords()[1].v = (tileY + tileHeight) / imageHeight;
				frame.GetUVCords()[2].u = tileX / imageWidth;
				frame.GetUVCords()[2].v = (tileY + tileHeight) / imageHeight;
				frame.GetUVCords()[3].u = tileX / imageWidth;
				frame.GetUVCords()[3].v = tileY / imageHeight;
				newTile.SetTextureCoordinates(frame);

				tileX += tileWidth;
				SetTile(newTile);

				_id++;
			}
			tileX = 0;
			tileY += tileHeight;
		}

		tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

		while (pTile)
		{
			unsigned int id = pTile->IntAttribute("id");
			tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
			std::string propertyName = pProperty->Attribute("value");

			tiles[id].SetWalkeable(propertyName == "true");
			tiles[id].SetCollider(true);

			pTile = pTile->NextSiblingElement("tile");
		}

		// Loading Layer element
		tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
		if (pLayer == NULL)
			return false;

		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData == NULL)
			return false;

		std::vector<int> tileGids;
		for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
			pTile != NULL;
			pTile = pTile->NextSiblingElement("tile"))
		{
			unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
			tileGids.push_back(gid);
		}

		int gid = 0;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (tileGids[gid] != 0)
				{
					SetMapTileId(0, y, x, tileGids[gid]);
				}

				gid++;
			}
		}

		pData = pData->NextSiblingElement("data");

		return true;
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
		for (int i = 0; i < height; i++)
		{
			tileMap[i] = new Tile[width];
		}
		grid.push_back(tileMap);
	}

	void Tilemap::SetSize(float size)
	{
		float mapWidth = -(width * tileWidth / 2.f);
		float mapHeight = height * tileHeight / 2.f;

		for (int i = 0; i < grid.size(); i++)
		{
			for (int y = 0; y < this->height; y++)
			{
				for (int x = 0; x < this->width; x++)
				{
					if (grid[i][y][x].GetId() != NULL)
					{
						glm::vec3 pos = glm::vec3(.0f, .0f, .0f);
						pos.x = (mapWidth + (tileWidth * x)) * size;
						pos.y = (mapHeight - (tileHeight * y)) * size;
						grid[i][y][x].SetPos(pos);
						grid[i][y][x].SetScale(tileWidth * size, tileHeight * size, 1.f);
					}
				}
			}
		}

		tileWidth *= size;
		tileHeight *= size;
	}

	void Tilemap::Draw()
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (grid[i][y][x].GetId() != NULL)
					{
						grid[i][y][x].Draw();
					}
				}
			}
		}
	}

	void Tilemap::DeInit()
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (grid[i][y][x].GetId() != NULL)
					{
						grid[i][y][x].DeInit();
					}
				}
			}
		}
	}

	void Tilemap::CheckCollision(Entity2D* entity)
	{
		float convertedPosX = entity->GetPosX() + (width / 2) * tileWidth;
		float convertedPosY = entity->GetPosY() - (height / 2) * tileHeight;

		int left_tile = convertedPosX / tileWidth;
		int right_tile = (convertedPosX + entity->GetScaleX()) / tileWidth;

		int top_tile = (convertedPosY / tileHeight) * -1;
		int bottom_tile = ((convertedPosY - entity->GetScaleY()) / tileHeight) * -1;

		if (left_tile < 0)
			left_tile = 0;

		if (right_tile >= width)
			right_tile = width - 1;

		if (top_tile < 0)
			top_tile = 0;

		if (bottom_tile >= height)
			bottom_tile = height - 1;

		for (int i = left_tile; i <= right_tile; i++)
		{
			for (int j = top_tile; j <= bottom_tile; j++)
			{
				for (int k = 0; k < grid.size(); k++)
				{
					if (!grid[k][j][i].IsWalkeable())
					{
						Collision::CollisionUpdate(&grid[k][j][i], entity);
					}
				}
			}
		}
	}
}