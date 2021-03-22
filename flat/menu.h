#pragma once
#define WIN32_LEAN_AND_MEAN

#include "image.h"
//#include "textureManager.h"
#include "graphics.h"
#include "input.h"
#include "page.h"
#include "constants.h"
//#include "flat.h"

class Menu : public Page
{
private:

	// Tutorial button
	Image tutorial;
	// Start button
	//TextureManager startTexture;
	Image start;

	// Quit Button
	//TextureManager quitTexture;
	Image quit;

	// Credits Button
	//TextureManager creditsTexture;
	Image credits;

	// Instructions Button
	//TextureManager instructionsTexture;
	Image instructions;

	// Leaderboards Button
	//TextureManager leaderboardsTexture;
	Image leaderboards;

	// Main Menu Background
	//TextureManager menuBgTexture;
	Image menuBg;

	// instructions screen background
	//TextureManager insBgTexture;
	Image insBg;

	// Back button 
	//TextureManager backTexture;
	Image back;

	// Credits screen background
	//TextureManager crBgTexture;
	Image crBg;

	// Start screen 
	//TextureManager startscrTexture;
	Image startscr;
	
public:
	Menu();
	~Menu();
	void initPictures(Graphics * graphics);
	void initialize(Graphics* graphics, Input* input);
	void releaseAll();
	void resetAll();
	PageType update(float frameTime);
	void render();


	bool showInstructions;

	bool showCredits;

	bool showBg;

	bool startscreen;

	int timer;


};

