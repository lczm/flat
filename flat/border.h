#pragma once
#define WIN_32_LEAN_AND_MEAN

#include "image.h"

class Border
{
private:
	Image* redBorder;
	Image* blueBorder;
	Image* greenBorder;
	Image* orangeBorder;
public:
	Border();
	~Border();
	void initialize(Image* redBorder, Image* blueBorder, 
		Image* greenBorder, Image* orangeBorder);
	SpriteData getSpriteData(BorderType borderType);
};