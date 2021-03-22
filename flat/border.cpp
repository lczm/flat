#include "border.h"

Border::Border()
{}

Border::~Border()
{}

void Border::initialize(Image* redBorder, Image* greenBorder,
	Image* blueBorder, Image* orangeBorder)
{
	Border::redBorder = redBorder;
	Border::greenBorder = greenBorder;
	Border::blueBorder = blueBorder;
	Border::orangeBorder = orangeBorder;
}

SpriteData Border::getSpriteData(BorderType borderType)
{
	Image* image = NULL;
	switch (borderType)
	{
	case BorderType::RED:
		image = redBorder;
		break;
	case BorderType::BLUE:
		image = blueBorder;
		break;
	case BorderType::GREEN:
		image = greenBorder;
		break;
	case BorderType::ORANGE:
		image = orangeBorder;
		break;
	}
	return image->getSpriteData(0);
}