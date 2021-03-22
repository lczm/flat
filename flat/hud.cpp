#include "hud.h"

HUD::HUD()
{
	initialized = false;	// true when successfully initialized
	graphics = NULL;		// pointer to graphics
	backColor = hudNS::BACK_COLOR;		// color of primitive
	damageYIncrement = 0;				// Y-axis offset of damage indicator
	vertexBuffer = NULL;				// vertex buffer for primitive
	shopPage = 1;						// page of shop
	spriteText = new SpriteText();
	tooltipText = "Select a unit to move it or click on the castle\nto purchase a unit!";

	// defining images
	unitInfoBox = new Image();
	shopBox = new Image();
	smallBtn = new Image();
	archerSprite = new Image();
	cavalrySprite = new Image();
	spearmanSprite = new Image();
	healthBar = new Image();
	endBox = new Image();
	endBtn = new Image();
	squareBox = new Image();
	smallSquareBox = new Image();
	backgroundImage = new Image();
	largeSquareBox = new Image();
	tooltipBox = new Image();
	swordTile = new Image();
}

HUD::~HUD()
{
	SAFE_DELETE(spriteText);
}

bool HUD::initialize(Graphics* graphics, Input* input)
{
	try {
		HUD::graphics = graphics;
		HUD::input = input;

		// defining vertex coordinates
		// vertex top left
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;
		// vertex top right
		vtx[1].x = x + hudNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;
		// vertex bottom right;
		vtx[2].x = x + hudNS::WIDTH;
		vtx[2].y = y + hudNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;
		// vertex bottom left
		vtx[3].x = x;
		vtx[3].y = y + hudNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;
		graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);


		// initializing sprite text and images
		if (!spriteText->initialize(graphics, FONT_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the sprite text"));
		if (!smallBtn->initialize(graphics, SMALLBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the small button sprite"));
		if (!unitInfoBox->initialize(graphics, MEDIUMBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the unit info box sprite"));
		if (!shopBox->initialize(graphics, LARGEBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the shop box sprite"));
		if (!archerSprite->initialize(graphics, BLUE_ARCHER_FILE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the archer sprite"));
		if (!cavalrySprite->initialize(graphics, BLUE_CAVALRY_FILE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the cavalry sprite"));
		if (!spearmanSprite->initialize(graphics, BLUE_SPEARMAN_FILE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the spearman sprite"));
		if (!healthBar->initialize(graphics, BAR_IMAGE, 235))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the health bar sprite"));
		if (!endBox->initialize(graphics, "images\\scorebox.png"))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the score box sprite"));
		if (!endBtn->initialize(graphics, "images\\submitbox.png"))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the submit box sprite"));
		if (!squareBox->initialize(graphics, SQUAREBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the square box sprite"));
		if (!smallSquareBox->initialize(graphics, SMALLSQUAREBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the small square box sprite"));
		if (!backgroundImage->initialize(graphics, BACKGROUND_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the background image sprite"));
		if (!largeSquareBox->initialize(graphics, LARGESQUAREBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the large square box sprite"));
		if (!tooltipBox->initialize(graphics, TOOLTIPBOX_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the tooltip box sprite"));
		if (!swordTile->initialize(graphics, SWORDBUFF_FILE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the tooltip box sprite"));

		// setting SpriteDatas and setting the scale coordinates for them
		swordTileSD = swordTile->getSpriteData(0);
		swordTileSD.scale = 3;
		swordTileSD.x = 95;
		swordTileSD.y = GAME_HEIGHT - 100;
		tooltipBoxSD = tooltipBox->getSpriteData(0);
		tooltipBoxSD.x = 510;
		tooltipBoxSD.y = GAME_HEIGHT - 115;
		totalHealthBarSD = healthBar->getSpriteData(0);
		totalHealthBarSD.x = GAME_WIDTH * 0.15;
		totalHealthBarSD.y = GAME_HEIGHT * 0.89;
		currentHealthBarSD = healthBar->getSpriteData(0);
		currentHealthBarSD.x = GAME_WIDTH * 0.15;
		currentHealthBarSD.y = GAME_HEIGHT * 0.89;
		smallBtnSD = smallBtn->getSpriteData(0);
		smallBtnSD.x = GAME_WIDTH * 0.315;
		smallBtnSD.y = GAME_HEIGHT * 0.75;
		smallBtnSD.scale = 0.8;
		leftBtnSD = smallBtn->getSpriteData(0);
		leftBtnSD.x = GAME_WIDTH * 0.03;
		leftBtnSD.y = GAME_HEIGHT * 0.75;
		leftBtnSD.scale = 0.8;
		rightBtnSD = smallBtn->getSpriteData(0);
		rightBtnSD.x = GAME_WIDTH * 0.14;
		rightBtnSD.y = GAME_HEIGHT * 0.75;
		rightBtnSD.scale = 0.8;
		unitInfoSD = unitInfoBox->getSpriteData(0);
		unitInfoSD.x = 30;
		unitInfoSD.y = GAME_HEIGHT - 115;
		shopSD = shopBox->getSpriteData(0);
		shopSD.x = GAME_WIDTH * 0.02;
		shopSD.y = GAME_HEIGHT * 0.38;
		closeShopSD = smallSquareBox->getSpriteData(0);
		closeShopSD.x = GAME_WIDTH * 0.39;
		closeShopSD.y = GAME_HEIGHT * 0.40;
		closeShopSD.scale = 0.45;
		btnSD = smallBtn->getSpriteData(0);
		btnSD.x = GAME_WIDTH - 200;
		btnSD.y = GAME_HEIGHT - 80;
		archerSD = archerSprite->getSpriteData(0);
		archerSD.x = GAME_WIDTH * 0.05;
		archerSD.y = GAME_HEIGHT * 0.42;
		archerSD.scale = 7;
		cavalrySD = cavalrySprite->getSpriteData(0);
		cavalrySD.x = GAME_WIDTH * 0.05;
		cavalrySD.y = GAME_HEIGHT * 0.42;
		cavalrySD.scale = 7;
		spearmanSD = spearmanSprite->getSpriteData(0);
		spearmanSD.x = GAME_WIDTH * 0.05;
		spearmanSD.y = GAME_HEIGHT * 0.42;
		spearmanSD.scale = 7;
		exitToMenuSD = smallBtn->getSpriteData(0);
		exitToMenuSD.x = GAME_WIDTH - 160;
		exitToMenuSD.y = 70;
		exitToMenuSD.scale = 0.8;
		endBoxSD = endBox->getSpriteData(0);
		endBoxSD.x = GAME_WIDTH / 2 - endBoxSD.width / 2;
		endBoxSD.y = GAME_HEIGHT / 2 - endBoxSD.height / 2;
		endBtnSD = endBtn->getSpriteData(0);
		endBtnSD.y = endBoxSD.y + endBoxSD.height - endBtnSD.height - 40;
		endBtnSD.x = GAME_WIDTH / 2 - endBtnSD.width / 2;
		minimapBorderSD = squareBox->getSpriteData(0);
		minimapBorderSD.x = 14;
		minimapBorderSD.y = 70;
		minimapBorderSD.scale = 0.37;
		playfieldBackgroundSD = largeSquareBox->getSpriteData(0);
		magnifyMapSD = smallSquareBox->getSpriteData(0);
		magnifyMapSD.x = GAME_WIDTH * 0.95;
		magnifyMapSD.y = GAME_HEIGHT * 0.74;
		magnifyMapSD.scale = 0.65;
		minifyMapSD = smallSquareBox->getSpriteData(0);
		minifyMapSD.x = GAME_WIDTH * 0.95;
		minifyMapSD.y = GAME_HEIGHT * 0.81;
		minifyMapSD.scale = 0.65;
		backgroundSD = backgroundImage->getSpriteData(0);
		backgroundSD.y = GAME_HEIGHT - backgroundSD.height;
	}
	catch (...) {
		return false;
	}
	initialized = true;
	return true;
}

void HUD::draw(std::string turn, std::string gold)
{
	if (graphics == NULL || !initialized)
		return;
	
	spriteText->setProportional(true);				// setting proportional font spacing
	spriteText->setFontColor(graphicsNS::BLACK);	// setting font color
	spriteText->setBackColor(TRANSCOLOR);			// setting the background color to be the transcolor so that the font will have a transparent background when printed
	spriteText->setFontHeight(hudNS::FONT_HEIGHT);  // setting font size
	graphics->spriteEnd();						
	graphics->drawQuad(vertexBuffer);				// draw the primitive
	graphics->spriteBegin();
	// printing and drawing hud elements
	spriteText->print("PLAYER PHASE", GAME_WIDTH * 0.02, GAME_HEIGHT * 0.005);	
	spriteText->print("TURN " + turn, GAME_WIDTH * 0.45, GAME_HEIGHT * 0.005);
	spriteText->print("GOLD: " + gold, GAME_WIDTH * 0.78, GAME_HEIGHT * 0.005);
	graphics->drawSprite(btnSD);
	spriteText->setFontHeight(27);
	spriteText->print("END TURN", GAME_WIDTH * 0.87, GAME_HEIGHT * 0.93);
	graphics->drawSprite(magnifyMapSD);
	graphics->drawSprite(minifyMapSD);
	graphics->drawSprite(tooltipBoxSD);
	graphics->drawSprite(exitToMenuSD);
	spriteText->print("EXIT", GAME_WIDTH - 120, 80);
	spriteText->print("+", GAME_WIDTH * 0.966, GAME_HEIGHT * 0.76);
	spriteText->print("-", GAME_WIDTH * 0.966, GAME_HEIGHT * 0.8345);
	spriteText->setFontHeight(20);
	spriteText->print(tooltipText, 520, GAME_HEIGHT - 110);
}

// draw the minimap border
void HUD::drawMinimapBorder()
{
	graphics->drawSprite(minimapBorderSD);
}

// drawing the background of the level
void HUD::drawPlayfieldBackground(float x, float y, float scale)
{
	graphics->drawSprite(backgroundSD);
	playfieldBackgroundSD.x = x - (5 * scale);
	playfieldBackgroundSD.y = y - (5 * scale);
	playfieldBackgroundSD.scale = scale / 4;
	graphics->drawSprite(playfieldBackgroundSD);
}


// drawing the unit info when the unit is selected
void HUD::drawUnitInfo(SpriteData unitSprite, int currentHP, int maxHP, std::string atk, std::string mov, bool buffed)
{
	currentHealthBarSD.rect.right = 235 * ((float)currentHP / (float)maxHP);
	unitSprite.scale = 4;
	unitSprite.x = 40;
	unitSprite.y = GAME_HEIGHT - 100;
	graphics->drawSprite(unitInfoSD);
	graphics->drawSprite(unitSprite);
	graphics->drawSprite(totalHealthBarSD, graphicsNS::RED);
	graphics->drawSprite(currentHealthBarSD, graphicsNS::GREEN);
	if (buffed)
	{
		graphics->drawSprite(swordTileSD);
		spriteText->print("1", 125, GAME_HEIGHT - 100);
	}
	spriteText->setFontHeight(27);
	spriteText->print("HP : " + std::to_string(currentHP) + "/" + std::to_string(maxHP), 140, GAME_HEIGHT * 0.89);
	spriteText->print("ATK : " + atk, 140, GAME_HEIGHT * 0.93);
	spriteText->print("MOV : " + mov, 320, GAME_HEIGHT * 0.93);
}


// drawing the unit shop
void HUD::drawShop()
{
	graphics->drawSprite(shopSD);			// draw the shop background
	graphics->drawSprite(closeShopSD);
	spriteText->print("x", GAME_WIDTH * 0.399, GAME_HEIGHT * 0.41);
	if (shopPage == 1)					// if the shop is on the first page, draw the archer unit info
	{
		graphics->drawSprite(rightBtnSD);
		archerSD.rect.right = archerSD.width / 2;
		graphics->drawSprite(archerSD);	
		spriteText->setFontHeight(50);
		spriteText->print(">", GAME_WIDTH * 0.188, GAME_HEIGHT * 0.756);
		spriteText->setFontHeight(30);
		spriteText->print("Archer", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.56);
		spriteText->setFontHeight(27);
		spriteText->print("HP : 10", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.62);
		spriteText->print("RANGE : 3", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.67);
		spriteText->print("ATK : 8", GAME_WIDTH * 0.18, GAME_HEIGHT * 0.62);
		spriteText->print("MOV : 3", GAME_WIDTH * 0.18, GAME_HEIGHT * 0.67);
		spriteText->print("$2000", GAME_WIDTH * 0.325, GAME_HEIGHT * 0.71);
		spriteText->setFontHeight(25);
		spriteText->print("DESCRIPTION", GAME_WIDTH * 0.2, GAME_HEIGHT * 0.42);
		spriteText->setFontHeight(20);
		spriteText->print("The archer is a long\nranged unit that\nspecializes in long\nrange.", GAME_WIDTH * 0.2, GAME_HEIGHT * 0.47);
	}
	else if (shopPage == 2)			// if the shop is on the second page, draw the cavalry unit info
	{
		graphics->drawSprite(leftBtnSD);
		graphics->drawSprite(rightBtnSD);
		cavalrySD.rect.right = cavalrySD.width / 2;
		graphics->drawSprite(cavalrySD);
		spriteText->setFontHeight(50);
		spriteText->print("<", GAME_WIDTH * 0.07, GAME_HEIGHT * 0.756);
		spriteText->print(">", GAME_WIDTH * 0.188, GAME_HEIGHT * 0.756);
		spriteText->setFontHeight(30);
		spriteText->print("Cavalry", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.56);
		spriteText->setFontHeight(27);
		spriteText->print("HP : 20", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.62);
		spriteText->print("RANGE : 2", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.67);
		spriteText->print("ATK : 15", GAME_WIDTH * 0.18, GAME_HEIGHT * 0.62);
		spriteText->print("MOV : 3", GAME_WIDTH * 0.18, GAME_HEIGHT * 0.67);
		spriteText->print("$3000", GAME_WIDTH * 0.325, GAME_HEIGHT * 0.71);
		spriteText->setFontHeight(25);
		spriteText->print("DESCRIPTION", GAME_WIDTH * 0.2, GAME_HEIGHT * 0.42);
		spriteText->setFontHeight(20);
		spriteText->print("The cavalry is\non a horse.", GAME_WIDTH * 0.2, GAME_HEIGHT * 0.47);
	}
	else                           // otherwise, draw the spearman unit's info
	{
		graphics->drawSprite(leftBtnSD);
		spearmanSD.rect.right = spearmanSD.width / 2;
		graphics->drawSprite(spearmanSD);
		spriteText->setFontHeight(50);
		spriteText->print("<", GAME_WIDTH * 0.07, GAME_HEIGHT * 0.756);
		spriteText->setFontHeight(30);
		spriteText->print("Spearman", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.56);
		spriteText->setFontHeight(27);
		spriteText->print("HP : 15", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.62);
		spriteText->print("RANGE : 1", GAME_WIDTH * 0.04, GAME_HEIGHT * 0.67);
		spriteText->print("ATK : 10", GAME_WIDTH * 0.18, GAME_HEIGHT * 0.62);
		spriteText->print("MOV : 2", GAME_WIDTH * 0.18, GAME_HEIGHT * 0.67);
		spriteText->print("$1000", GAME_WIDTH * 0.325, GAME_HEIGHT * 0.71);
		spriteText->setFontHeight(25);
		spriteText->print("DESCRIPTION", GAME_WIDTH * 0.2, GAME_HEIGHT * 0.42);
		spriteText->setFontHeight(20);
		spriteText->print("The spearman is\nholding a spear.", GAME_WIDTH * 0.2, GAME_HEIGHT * 0.47);
	}
	graphics->drawSprite(smallBtnSD);			// draw the buy button sprite
	spriteText->setFontHeight(38);
	spriteText->print("BUY", GAME_WIDTH * 0.337, GAME_HEIGHT * 0.758);
}

// if the end turn button has been clicked, return true else return false
bool HUD::endButtonClick(int screenX, int screenY)
{
    SpriteData sd = btnSD;
    if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
        screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
        return true;
    }
    return false;
}

// if the next shop page button has been clicked, return true else return false
bool HUD::nextPageClick(int screenX, int screenY)
{
	SpriteData sd = rightBtnSD;
    if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
        screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
        return true;
    }
    return false;
}

// if the previous shop page button has been clicked, return true else return false
bool HUD::prevPageClick(int screenX, int screenY)
{
	SpriteData sd = leftBtnSD;
    if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
        screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
        return true;
    }
    return false;
}

bool HUD::exitClick(int screenX, int screenY)
{
	SpriteData sd = exitToMenuSD;
    if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
        screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
        return true;
    }
    return false;
}

// if the buy unit button has been clicked, return true else return false
bool HUD::buyUnitClick(int screenX, int screenY)
{
	SpriteData sd = smallBtnSD;
    if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
        screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
        return true;
    }
    return false;
}

bool HUD::closeShopClick(int screenX, int screenY)
{
	SpriteData sd = closeShopSD;
    if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
        screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
        return true;
    }
    return false;
}

// if the minify map button has been clicked, return true else return false
bool HUD::minifyMapClick(int screenX, int screenY)
{
	SpriteData sd = minifyMapSD;
	if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
		screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
		return true;
	}
	return false;
}

// if the magnify map button has been clicked, return true else return false
bool HUD::magnifyMapClick(int screenX, int screenY)
{
	SpriteData sd = magnifyMapSD;
	if (screenX >= sd.x && screenX <= sd.x + (sd.width * sd.scale) &&
		screenY >= sd.y && screenY <= sd.y + (sd.height * sd.scale)) {
		return true;
	}
	return false;
}

// draw the damage indicators when a unit is hit
/*	how it works :
1. if the bool showDamageIndicator is true and the damageYIncrement is less than 40, it draws the damage taken by the unit
   (damageYIncrement is the Y offset of the damage indicator that increases by 1 every frame to simulate a rising damage indicator number)
2. then draw the damage indicator with the y offset indicated in damageYIncrement
3. else set showDamageIndicator = false and reset the damageYIncrement back to 0
*/
void HUD::damagePopUp(float scale)
{
	if (showDamageIndicator && damageYIncrement < 40)
	{
		//graphics->spriteBegin();
		spriteText->setFontHeight(15 * scale);
		spriteText->print(std::to_string(attackingUnitDmg), attackedUnitX, attackedUnitY - damageYIncrement);
		damageYIncrement += 1;
	}
	else
	{
		showDamageIndicator = false;
		damageYIncrement = 0;
	}
}

// returns the type of unit the player buys when they click the buy button
// based on the page number that they are at
UnitType HUD::buyUnit()
{
	if (shopPage == 1)
	{
		return UnitType::ARCHER;
	}
	else if (shopPage == 2)
	{
		return UnitType::CAVALRY;
	}
	else
	{
		return UnitType::SPEARMAN;
	}
}

// draw the unit's HP bar based on the coordinates of the unit
// the HP bar is two rectangle bar images layered on top of each other
// the image that is below is a red color while the one overlayed on it is green
// when the unit takes damage, the length of the green HP bar is reduced
// based on the ratio of the unit's current HP and the unit's max HP
void HUD::drawUnitHPBar(float x, float y, int width, float scale, int currentHP, int maxHP)
{
	float hpScale = scale * 0.05;
	x += 8;
	unitCurrentHealthBarSD = healthBar->getSpriteData(0);
	unitTotalHealthBarSD = healthBar->getSpriteData(0);
	unitCurrentHealthBarSD.rect.right = 235 * ((float)currentHP / (float)maxHP);
	unitCurrentHealthBarSD.x = x;
	unitCurrentHealthBarSD.y = y;
	unitCurrentHealthBarSD.scale = hpScale;
	unitTotalHealthBarSD.x = x;
	unitTotalHealthBarSD.y = y;
	unitTotalHealthBarSD.scale = hpScale;
	graphics->drawSprite(unitTotalHealthBarSD, graphicsNS::RED);
	graphics->drawSprite(unitCurrentHealthBarSD, graphicsNS::BLUE);
}

void HUD::releaseAll()
{
	spriteText->onLostDevice();
	return;
}

void HUD::resetAll()
{
	spriteText->onResetDevice();
	return;
}

void HUD::drawEndBox(std::string title, int score, std::string name, std::string btn) {
	spriteText->setFontHeight(60);
	graphics->drawSprite(endBoxSD);
	graphics->drawSprite(endBtnSD);
	int left = endBoxSD.x + 60;
	int top = endBoxSD.y + 60;
	spriteText->print(title, left, top);
	spriteText->print("Score: " + std::to_string(score), left, top + 100);
	if (!std::empty(name)) spriteText->print("Name: " + name, left, top + 200);
	spriteText->print(btn, GAME_WIDTH / 2, endBtnSD.y + 45, textNS::CENTER);
}

bool HUD::endBtnClick() {
	int relX = input->getMouseX() - endBtnSD.x;
	int relY = input->getMouseY() - endBtnSD.y;
	return (0 < relX && relX < endBtnSD.width && 
			0 < relY && relY < endBtnSD.height);
}