#ifndef _HUD_H
#define _HUD_H
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "spriteText.h"
#include "unit.h"
#include <deque>
#include <string>

class HUD;

namespace hudNS
{
	const UINT WIDTH = GAME_WIDTH;
	const UINT HEIGHT = 45;
	const int FONT_HEIGHT = 35;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = D3DCOLOR_ARGB(255, 237, 128, 46);
}

class HUD
{
private:
	Graphics* graphics;						// pointer to graphics
	Input* input;							// pointer to input
	SpriteText* spriteText;					// pointer to spriteText
	float x, y;								// x and y for primitive coordinates
	float attackedUnitX, attackedUnitY;		// x and y coordinates of the attacked unit
	int attackingUnitDmg;					// attack power of the attacking unit
	int damageYIncrement;					// y offset of the damage indicator
	COLOR_ARGB backColor;					// background color of the primitive
	VertexC vtx[4];							// array of vertices for the primitive
	LP_VERTEXBUFFER vertexBuffer;			// vertex buffer for the primitive
	bool initialized;						// hud initialization bool
	int shopPage;							// page of the shop
	bool showDamageIndicator;				// bool to check whether to show the damage indicator or not
	std::string tooltipText;

	// image pointer declarations
	Image* unitInfoBox;						
	Image* shopBox;
	Image* smallBtn;
	Image* archerSprite;
	Image* cavalrySprite;
	Image* spearmanSprite;
	Image* healthBar;
	Image* endBox;
	Image* endBtn;
	Image* squareBox;
	Image* smallSquareBox;
	Image* backgroundImage;
	Image* largeSquareBox;
	Image* tooltipBox;
	Image* swordTile;

	// spritedata declarations
	SpriteData totalHealthBarSD;
	SpriteData currentHealthBarSD;
	SpriteData unitTotalHealthBarSD;
	SpriteData unitCurrentHealthBarSD;
	SpriteData archerSD;
	SpriteData cavalrySD;
	SpriteData spearmanSD;
	SpriteData shopSD;
	SpriteData unitInfoSD;
	SpriteData btnSD;
	SpriteData smallBtnSD;
	SpriteData rightBtnSD;
	SpriteData leftBtnSD;
	SpriteData endBoxSD;
	SpriteData endBtnSD;
	SpriteData minimapBorderSD;
	SpriteData magnifyMapSD;
	SpriteData minifyMapSD;
	SpriteData playfieldBackgroundSD;
	SpriteData backgroundSD;
	SpriteData closeShopSD;
	SpriteData tooltipBoxSD;
	SpriteData exitToMenuSD;
	SpriteData swordTileSD;

public:
	HUD();
	virtual ~HUD();
	bool initialize(Graphics* graphics, Input* input);			// initialize the HUD
	void draw(std::string turn, std::string gold);				// draw the main HUD elements
	void drawUnitInfo(SpriteData unitSprite, int currentHP, int maxHP, std::string atk, std::string mov, bool buffed);		// draw the unit info when it is selected
	void drawShop();											// draw the shop
	void drawMinimapBorder();									// draw the minimap border
	void drawPlayfieldBackground(float x, float y, float scale);	// draw the background image of the level
	void drawUnitHPBar(float x, float y, int width, float scale, int currentHP, int maxHP);		// draw the HP bar of the unit
    bool endButtonClick(int screenX, int screenY);				// check if the end turn button has been clicked
	bool nextPageClick(int screenX, int screenY);				// check if the next page button has been clicked
	bool prevPageClick(int screenX, int screenY);				// check if the previous page button has been clicked
	bool magnifyMapClick(int screenX, int screenY);				// check if the magnify map button has been clicked
	bool minifyMapClick(int screenX, int screenY);				// check if the minify map button has been clicked
	bool buyUnitClick(int screenX, int screenY);				// check if the buy unit button has been clicked
	bool exitClick(int screenX, int screenY);				// check if the buy unit button has been clicked
	bool closeShopClick(int screenX, int screenY);				// check if the buy unit button has been clicked
	void damagePopUp(float scale);								// draw the damage indicator
	void setTooltipText(std::string text) { tooltipText = text; }
	UnitType buyUnit();											// return the type of unit bought
	void toggleShowDamageIndicator() { showDamageIndicator = true; }		// set the showDamageIndicator bool to true
	void setAttackedUnitXY(float unitX, float unitY) { attackedUnitX = unitX; attackedUnitY = unitY; }		// setting the attacked unit's x and y coordinates
	void setAttackingUnitDmg(int dmg) { attackingUnitDmg = dmg; }											// setting the attacking unit's attack power
	void releaseAll();
	void resetAll();
	void nextPage() { if (shopPage < 3) shopPage += 1; }		// change to next page of shop
	void prevPage() { if (shopPage > 1) shopPage -= 1; }		// change to previous page of shop
	void drawEndBox(std::string title, int score, std::string name, std::string btn);
	bool endBtnClick();
};

#endif