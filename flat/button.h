#pragma once
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"
#include "input.h"
#include "image.h"
#include "spriteText.h"

using namespace std;

class Button
{
private:
	Graphics* graphics;
	SpriteText* spriteText;
	Input* input;
	Image* image;
	int frameNo;
	PageType pageType;
	string text;
	int fontSize;
	int x;
	int y;
	int scale;

public:
	Button();
	~Button();
	void initialize(
		Graphics* graphics, Input* input, Image* image, 
		SpriteText* spriteText, PageType pageType, 
		string text, int x, int y);
	void setFrameNo(int frameNo) { Button::frameNo = frameNo; }
	void setPageType(PageType pageType) { Button::pageType = pageType; };
	void setText(string text) { Button::text = text; }
	void setFontSize(int fontSize) { Button::fontSize = fontSize; }
	void setPos(int x, int y) { Button::x = x; Button::y = y; };
	void setScale(int scale) { Button::scale = scale; }

	void draw();
	bool isClick();
};