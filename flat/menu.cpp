#include "menu.h"

Menu::Menu()
{
	showInstructions = false;
	showBg = false;
	showCredits = false;
	startscreen = true;
}


Menu::~Menu()
{

}

void Menu::initPictures(Graphics * graphics)
{
	//Initializing textures
	//if (!startTexture.initialize(graphics, START_BTN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); //Start Button Texture

	//if (!quitTexture.initialize(graphics, QUIT_BTN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); // Quit Button Texture

	//if (!creditsTexture.initialize(graphics, CREDITS_BTN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); // Credits Button Texture 

	//if (!instructionsTexture.initialize(graphics, INSTR_BTN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); // Instructions Button Texture

	//if (!leaderboardsTexture.initialize(graphics, LEAD_BTN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); // Leaderboard Button Texture

	//if (!backTexture.initialize(graphics, BACK_BTN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); //Back Button Image

	//if (!menuBgTexture.initialize(graphics, MENU_BG))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); //Menu Background Image

	//if (!insBgTexture.initialize(graphics, INS_BG))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); //Instruction screen Background Image


	//if (!crBgTexture.initialize(graphics, CREDITS_BG))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); //Credits Screen Background Image

	//if (!startscrTexture.initialize(graphics, START_SCRN))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite texture")); // Start Screen Image
	
																						 
	// Initializing Images
	if (!tutorial.initialize(graphics, START_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Start Button"));		

	if (!start.initialize(graphics, START_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Start Button"));		

	if (!quit.initialize(graphics, QUIT_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Quit Button"));

	if (!credits.initialize(graphics, CREDITS_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Credtis Button"));

	if (!instructions.initialize(graphics, INSTR_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Instructions Button"));

	if (!leaderboards.initialize(graphics, LEAD_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Instructions Button"));

	if (!menuBg.initialize(graphics, MENU_BG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Menu Background"));

	if (!insBg.initialize(graphics, INS_BG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Menu Background"));

	if (!back.initialize(graphics, BACK_BTN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Menu Background"));

	if (!crBg.initialize(graphics, CREDITS_BG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Menu Background"));

	if (!startscr.initialize(graphics, START_SCRN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Menu Background"));


	//Positions of each button

	//Background Image (X,Y)
	menuBg.setX(0);
	menuBg.setY(0);

	tutorial.setX(GAME_WIDTH / 2 - tutorial.getWidth() / 2);
	tutorial.setY(GAME_HEIGHT / 4 - 100);
	// Start Button (X,Y)
	start.setX(GAME_WIDTH / 2 - start.getWidth() / 2);
	start.setY(GAME_HEIGHT / 4);

	// Instructions Button (X,Y)
	instructions.setX(GAME_WIDTH / 2 - instructions.getWidth() / 2);
	instructions.setY(start.getY() + start.getHeight() + 30);

	leaderboards.setX(GAME_WIDTH / 2 - leaderboards.getWidth() / 2);
	leaderboards.setY(instructions.getY() + instructions.getHeight() + 30);

	// Credits Button (X,Y)
	credits.setX(GAME_WIDTH / 2 - credits.getWidth() / 2);
	credits.setY(leaderboards.getY() + leaderboards.getHeight() + 30);


	// Quit Button (X,Y)
	quit.setX(GAME_WIDTH / 2 - quit.getWidth() / 2);
	quit.setY(credits.getY() + credits.getHeight() + 30);

	insBg.setX(0);
	insBg.setY(0);

	back.setX(back.getWidth()/2);
	back.setY(back.getWidth() / 2);

	crBg.setX(0);
	crBg.setY(0);

	startscr.setX(0);
	startscr.setY(0);
	
}

void Menu::initialize(Graphics * graphics, Input * input)
{
	Page::initialize(graphics, input);
	initPictures(graphics);
}

void Menu::releaseAll()
{
	start.onLostDevice();
	quit.onLostDevice();
	credits.onLostDevice();
	instructions.onLostDevice();
	leaderboards.onLostDevice();
	menuBg.onLostDevice();
	insBg.onLostDevice();
	crBg.onLostDevice();
	// JX: Did u forgot startscr?
}

void Menu::resetAll()
{
	start.onResetDevice();
	quit.onResetDevice();
	credits.onResetDevice();
	instructions.onResetDevice();
	leaderboards.onResetDevice();
	menuBg.onResetDevice();
	insBg.onResetDevice();
	crBg.onResetDevice();
}

PageType Menu::update(float frameTime)
{
	int mouseX = getInput()->getMouseX();
	int mouseY = getInput()->getMouseY();

	if (getInput()->getMouseLButton())
	{
		if (mouseX > startscr.getX() && mouseX < startscr.getX() + startscr.getWidth())
		{
			if (mouseY > startscr.getY() && mouseY < start.getY() + startscr.getHeight())
			{
				startscreen = false;
				showBg = true;
				//return PageType::MAIN_MENU;	
			}
		}
	}

	if (getInput()->getMouseLButton())
	{
		if (mouseX > tutorial.getX() && mouseX < tutorial.getX() + tutorial.getWidth())
		{
			if (mouseY > tutorial.getY() && mouseY < tutorial.getY() + tutorial.getHeight())
			{
				return PageType::TUTORIAL; 
			}
		}
	}
	
	if (getInput()->getMouseLButton())
	{
		if (mouseX > start.getX() && mouseX < start.getX() + start.getWidth())
		{
			if (mouseY > start.getY() && mouseY < start.getY() + start.getHeight())
			{
				return PageType::LEVEL; 
			}
		}
	}

	if (getInput()->getMouseLButton())
	{
		if (mouseX > quit.getX() && mouseX < quit.getX() + quit.getWidth())
		{
			if (mouseY> quit.getY() && mouseY < quit.getY() + quit.getHeight())
			{
				PostQuitMessage(0);
			}
		}
	}

	if (getInput()->getMouseLButton())
	{
		if (mouseX > instructions.getX() && mouseX < instructions.getX() + instructions.getWidth())
		{
			if (mouseY > instructions.getY() && mouseY < instructions.getY() + instructions.getHeight())
			{
					showInstructions = true;
					showBg = false;

				return PageType::INSTRUCTION;
			}
		}
	}

	if (getInput()->getMouseLButton())
	{
		if (mouseX > leaderboards.getX() && mouseX < leaderboards.getX() + leaderboards.getWidth())
		{
			if (mouseY > leaderboards.getY() && mouseY < leaderboards.getY() + leaderboards.getHeight())
			{
				showBg = false;
				showInstructions = false;
				back.draw();

				return PageType::LEADERBOARD;
			}
		}
	}

	if (getInput()->getMouseLButton())
	{
		if (mouseX > back.getX() && mouseX < back.getX() + back.getWidth())
		{
			if (mouseY> back.getY() && mouseY < back.getY() + back.getHeight())
			{
				showInstructions = false;
				showCredits = false;
				showBg = true;
				return PageType::MAIN_MENU;
			}
		}
	}

	if (getInput()->getMouseLButton())
	{
		if (mouseX > credits.getX() && mouseX < credits.getX() + credits.getWidth())
		{
			if (mouseY > credits.getY() && mouseY < credits.getY() + credits.getHeight())
			{
				showCredits = true;
				showBg = false;

				return PageType::CREDIT;
			}
		}
	}

	return PageType::MAIN_MENU;
}

void Menu::render()
{
	if (startscreen == true)
	{
		showBg = false;
		startscr.draw();
	}
	if (showBg == true)
	{
		startscreen = false;

		menuBg.draw();
		tutorial.draw();
		start.draw();
		instructions.draw();
		leaderboards.draw();
		credits.draw();
		quit.draw();
		
	}


	
	if (showInstructions == true) 
	{
		insBg.draw();
		back.draw();
		showBg = false;
		PageType::INSTRUCTION;
	}

	if (showCredits == true)
	{
		crBg.draw();
		back.draw();
		showBg = false;
		PageType::CREDIT;
	}
}
