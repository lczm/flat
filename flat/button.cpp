#include "button.h"

Button::Button()
{
	frameNo = 0;
	text = "";
	fontSize = 20;
	x = 0;
	y = 0;
	scale = 1;
}

Button::~Button()
{}

void Button::initialize(
	Graphics* graphics, Input* input, Image* image, SpriteText* spriteText, 
	PageType pageType, string text, int x, int y)
{
	Button::graphics = graphics;
	Button::input = input;
	Button::image = image;
	Button::spriteText = spriteText;
	Button::pageType = pageType;
	Button::text = text;
	Button::x = x;
	Button::y = y;
}

void Button::draw()
{
	spriteText->setFontHeight(fontSize);
	SpriteData sd = image->getSpriteData(0);
	sd.scale = scale;
	sd.x = x - sd.width * scale / 2;
	sd.y = y - sd.height * scale / 2;
	graphics->drawSprite(sd);
	spriteText->print(text, x, y - fontSize * 0.4, textNS::CENTER);
}

bool Button::isClick()
{
	if (!input->getMouseLButton()) return false;
	SpriteData sd = image->getSpriteData(0);
	int left = x - sd.width * scale / 2;
	int top = y - sd.height * scale / 2;
	int relX = input->getMouseX() - left;
	int relY = input->getMouseY() - top;
	return (0 < relX && relX < sd.width &&
			0 < relY && relY < sd.height);
}