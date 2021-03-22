#pragma once
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "game.h"
#include "page.h"
#include "level.h"
#include "leaderboard.h"
#include "menu.h"
#include "audio.h"

class Flat : public Game
{
private:
	Page* mainMenuPage;
	Page* settingsPage;
	Page* instructionsPage;
	Page* creditsPage;
	Page* levelSelectPage;
	Level* levelPage;
	Level* tutorialPage;
	Page* leaderboardPage;
	PageType currentPageType;
	Page* currentPage;
	bool reset;
	Audio* audio;

public:
    Flat();
    virtual ~Flat();
	void initialize(HWND hwnd);
    void releaseAll();
    void resetAll();
	void update();
	void render();
	Audio* getAudio() { return audio;  }

	void setCurrentPage(PageType pageType);
};

