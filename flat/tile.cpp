#include "tile.h"

Tile::Tile()
{}

Tile::~Tile()
{}

void Tile::initialize(Image* image, TileType tileType)
{
	Entity::initialize(image);
	switch (tileType)
	{
	case TileType::GRASS:
		Tile::resistance = 1;
		typeTile = TileType::GRASS;
		break;
	case TileType::FOREST:
		Tile::resistance = 4;
		typeTile = TileType::FOREST;
		break;
	case TileType::MOUNTAIN:
		typeTile = TileType::MOUNTAIN;
		break;
	case TileType::SETTLEMENT:
		typeTile = TileType::SETTLEMENT;
		Tile::resistance = 1;
		Tile::captured = FALSE;
		Tile::redOrBlue = 0;
		break;
	case TileType::CASTLE:
		typeTile = TileType::CASTLE;
		Tile::resistance = 4;
		Tile::health = 10;
        Tile::destroyed = FALSE;
		break;
    case TileType::WATER:
		typeTile = TileType::WATER;
        Tile::resistance = 100;
        break;
	case TileType::RUIN:
		typeTile = TileType::RUIN;
		Tile::resistance = 1;
        break;
	case TileType::SWORDBUFF:
		Tile::resistance = 1;
		typeTile = TileType::SWORDBUFF;
		break;
	}
}

//set a tile to any image
void Tile::setTile(Image* image, int num, TileType type)
{
	this->initialize(image + num, type);
}

COLOR_ARGB Tile::getColor()
{
	return color;
}
