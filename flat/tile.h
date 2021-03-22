#pragma once
#define WIN_32_LEAN_AND_MEAN


#include "entity.h"
#include <vector>
#include "constants.h"

class Tile : public Entity
{
private:
	TileType typeTile;
	int resistance;
	int health;
	bool captured;
	int redOrBlue;
	bool destroyed;
	bool border;
	COLOR_ARGB color = NULL;
public:
	Tile();
	~Tile();
	void initialize(Image* image, TileType tileType);
	void setTile(Image* image, int num, TileType type);
	TileType getType() { return typeTile; }
	COLOR_ARGB getColor();
	bool getBorder() { return border; }
	bool getSettlementControl() { return captured; }
	void setSettlementControl(bool b) { captured = b ;}
	void setBorder(bool border) { Tile::border = border; }
	int getResistance() { return resistance; }
	void setResistance(int b) { resistance = b; }
};