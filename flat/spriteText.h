#ifndef _SPRITETEXT_H
#define _SPRITETEXT_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "constants.h"
#include "image.h"

namespace textNS
{
	enum Alignment { LEFT, RIGHT, CENTER, CENTER_MIDDLE, CENTER_BOTTOM, LEFT_BOTTOM, RIGHT_BOTTOM };
	struct FontData
	{
		UINT left;
		UINT right;
	};

	const int FONT_BORDER = 3; // transparent border around font
	const int FONT_WIDTH = 51;
	const int FONT_HEIGHT = 51;
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER;
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;
	const int COLUMNS = 32;		// number of columns in font image
	const int ROWS = 3;		// number of rows in font image
	const int FRAMES = 1;		// frames of animation; 1 = not animated
	const double ANIM_DELAY = 0.0;	// delay between animation frames
	const int MAX_FONT_HEIGHT = 1000;
	const int MIN_CHAR = 0x0020; // minimum character code
	const int MAX_CHAR = 0x007E; // maximum character code
	const int PROPORTIONAL_SPACING = 5;	// pixels between 1:1 scaled characters
	const int TAB_SIZE = 8;
	const char UNDERLINE = '_';
	const char SOLID = 0x7F;	// solid block used for fill character ASCII $7F
	const int BOLD_SIZE = 4;	// pixel shift for bold display
}

class SpriteText : public Image
{
private:
	Image font;
	LP_TEXTURE textureData;
	char* file;					// name of texture file
	Graphics* graphics;			// pointer to graphics
	UINT width, height;			// width & height of a character
	textNS::FontData fontData[textNS::ROWS][textNS::COLUMNS];
	COLOR_ARGB color;
	COLOR_ARGB backColor;
	UINT fontHeight;
	UINT tabSize;
	UINT proportionalSpacing;
	bool proportional;
	bool underline;
	bool bold;
	textNS::Alignment align;

public:
	SpriteText();

	virtual ~SpriteText();

	virtual bool initialize(Graphics* g, const char* file);

	virtual void update(float frameTime) {};
	virtual void onLostDevice();
	virtual void onResetDevice();
	// set text at x and y
	void setXY(int x, int y);

	// print text
	virtual void print(const std::string& str);

	virtual void print(const std::string& str, int x, int y);

	// set string at x and y then print the string
	virtual void print(const std::string& str, int x, int y, textNS::Alignment align);

	// get width and height required to display the string
	virtual void getWidthHeight(const std::string& str, UINT& width, UINT& height);

	// set the font color
	virtual void setFontColor(COLOR_ARGB c) { color = c; }

	// get font color
	virtual COLOR_ARGB getFontColor() { return color; }

	// set background color of font
	virtual void setBackColor(COLOR_ARGB bc) { backColor = bc; }

	// get background color
	virtual COLOR_ARGB getBackColor() { return backColor; }

	// set the height of the font (pixels)
	virtual void setFontHeight(UINT height)
	{
		if (height == 0 || height > textNS::MAX_FONT_HEIGHT)	// invalid size
			return;
		fontHeight = height;
		spriteData.scale = (float)height / (float)textNS::FONT_HEIGHT;
	}

	// get font height
	virtual UINT getFontHeight() { return fontHeight; }

	// setting proportional spacing on or off
	virtual void setProportional(bool p) { proportional = p; }

	// get the current proportional spacing setting
	virtual bool getProportional() { return proportional; }

	// set the amount of spacing for proportional spacing
	virtual void setProportionalSpacing(UINT s) { proportionalSpacing = s; }

	// get proportional spacing size
	virtual UINT getProportionalSpacing() { return proportionalSpacing; }

	// set underline spacing on or off
	virtual void setUnderline(bool u) { underline = u; }

	// set bold on or off
	virtual void setBold(bool b) { bold = b; }

	// get bold setting
	virtual bool getBold() { return bold; }

	// set tab size
	virtual void setTabSize(UINT size)
	{
		if (size == 0)
			return;
		tabSize = size;
	}

	// get tab size
	virtual UINT getTabSize() { return tabSize; }

	// set the x and y's for the current string and alignment
	virtual void doAlign(const std::string & str);

	// draw the character spirte
	virtual void drawChar(UCHAR ch);

};

#endif