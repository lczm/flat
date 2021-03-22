#include "flat.h"

Flat::Flat()
{
	mainMenuPage = new Menu();
	settingsPage = new Page();
	instructionsPage = new Page();
	creditsPage = new Page();
	levelSelectPage = new Page();
	levelPage = new Level();
	tutorialPage = new Level();
	leaderboardPage = new Leaderboard();
	audio = new Audio();
	reset = false;
}

Flat::~Flat()
{
    releaseAll();
	delete mainMenuPage;
	delete settingsPage;
	delete instructionsPage;
	delete creditsPage;
	delete levelSelectPage;
	delete levelPage;
	delete tutorialPage;
	delete leaderboardPage;
}

void Flat::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
	mainMenuPage->initialize(graphics, input);
	settingsPage->initialize(graphics, input);
	instructionsPage->initialize(graphics, input);
	creditsPage->initialize(graphics, input);
	levelSelectPage->initialize(graphics, input);
	leaderboardPage->initialize(graphics, input);
	tutorialPage->initialize(graphics, input, 0);
	levelPage->initialize(graphics, input, 1);
	currentPage = mainMenuPage;

    audio = new Audio();
    if (*WAVE_BANK != '\0' && *SOUND_BANK != '\0')  // if sound files defined
    {
        if( FAILED( hr = audio->initialize() ) )
        {
            if( hr == HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ) )
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system because media file not found."));
            else
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system."));
        }
    }
	audio->playCue("bensound-epic");
}

void Flat::update()
{
	PageType pageType = currentPage->update(frameTime);
	if (pageType != currentPageType) {
		setCurrentPage(pageType);
		currentPage->start();
	}
}

void Flat::render()
{
	if (!initialized) return;
    graphics->spriteBegin();
	currentPage->render();
    graphics->spriteEnd();
}

void Flat::releaseAll()
{
	mainMenuPage->releaseAll();
	settingsPage->releaseAll();
	instructionsPage->releaseAll();
	creditsPage->releaseAll();
	levelSelectPage->releaseAll();
	levelPage->releaseAll();
	tutorialPage->releaseAll();
	currentPage->releaseAll();
	leaderboardPage->releaseAll();
	Game::releaseAll();
}

void Flat::resetAll()
{
	mainMenuPage->resetAll();
	settingsPage->resetAll();
	instructionsPage->resetAll();
	creditsPage->resetAll();
	levelSelectPage->resetAll();
	levelPage->resetAll();
	tutorialPage->resetAll();
	currentPage->resetAll();
	leaderboardPage->resetAll();
	Game::resetAll();
}

void Flat::setCurrentPage(PageType pageType)
{
	currentPageType = pageType;
	switch (pageType)
	{
	case PageType::MAIN_MENU:
		currentPage = mainMenuPage;
		reset = true;
		break;
	case PageType::SETTINGS:
		currentPage = settingsPage;
		reset = false;
		break;
	case PageType::INSTRUCTION:
		currentPage = instructionsPage;
		reset = false;
		break;
	case PageType::CREDIT:
		currentPage = creditsPage;
		reset = false;
		break;
	case PageType::LEVEL_SELECT:
		currentPage = levelSelectPage;
		reset = false;
		break;
	case PageType::LEADERBOARD:
		currentPage = leaderboardPage;
		reset = true;
		break;
	case PageType::LEVEL:
		// Reinitialize the level
		if (reset) {
            delete levelPage;
            levelPage = new Level();
            levelPage->initialize(graphics, input, 1);
		}
		currentPage = levelPage;
		reset = false;
		break;
	case PageType::TUTORIAL:
		if (reset) {
            delete tutorialPage;
            tutorialPage = new Level();
            tutorialPage->initialize(graphics, input, 0);
		}
		currentPage = tutorialPage;
		reset = false;
		break;
	}
}