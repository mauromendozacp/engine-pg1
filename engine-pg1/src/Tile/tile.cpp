#include "tile.h"

namespace GL
{
	Tile::Tile() : Sprite()
	{
		id = 0;
		isWalkeable = false;
	}

	Tile::Tile(Render* render) : Sprite(render)
	{
		id = 0;
		isWalkeable = false;
	}

	Tile::~Tile()
	{
	}

	unsigned int Tile::GetId()
	{
		return id;
	}

	void Tile::SetId(unsigned int id)
	{
		this->id = id;
	}

	bool Tile::IsWalkeable()
	{
		return isWalkeable;
	}

	void Tile::SetWalkeable(bool walkeable)
	{
		isWalkeable = walkeable;
	}
	void Tile::SetRender(Render* render)
	{
		this->render = render;
	}
}