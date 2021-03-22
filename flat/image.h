#pragma once
#define WIN_32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"

class Image
{
protected:
	Graphics* graphics;
	const char* file;
    SpriteData spriteData;
	int cols;
	bool initialized;
public:
    Image();
    ~Image();
	bool initialize(
		Graphics* graphics, const char* file, 
		int width = 0, int height = 0);
	void onLostDevice();
	void onResetDevice();
    int getCols() { return cols; }

	inline void setRect(int frameNo);
	SpriteData getSpriteData(int frameNo);

	int getX() { return spriteData.x; }
	int getY() { return spriteData.y; }
	void setX(int x) { spriteData.x = x; }
	void setY(int y) { spriteData.y = y; }
	int getWidth() { return spriteData.width; }
	int getHeight() { return spriteData.height; }
	void draw() { graphics->drawSprite(spriteData); }
};