#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) {ptr->onLostDevice();}}
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) {ptr->onResetDevice();}}

// Transparent color (magenta)
//#define TRANSCOLOR SETCOLOR_ARGB(0, 255, 0, 255)

// Transparent color (white)
#define TRANSCOLOR graphicsNS::WHITE
//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "Flat";
const char GAME_TITLE[] = "Flat";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1440;               // width of game in pixels
const UINT GAME_HEIGHT = 900;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY = VK_MENU;     // Alt key
const UCHAR ENTER_KEY = VK_RETURN;   // Enter key

//// Flat
enum class PageType {
	MAIN_MENU, SETTINGS, INSTRUCTION,
	CREDIT, LEVEL_SELECT, LEVEL, LEADERBOARD, TUTORIAL
};

// Audio stuff
// Wave_Bank
const char WAVE_BANK[] = "audio\\Win\\Wave_Bank.xwb";
// Sound_Bank
const char SOUND_BANK[] = "audio\\Win\\Sound_Bank.xsb";


// Menu
const char START_BTN[] = "images\\start_button.png";
const char QUIT_BTN[] = "images\\quit_button.png";
const char CREDITS_BTN[] = "images\\credits_button.png";
const char INSTR_BTN[] = "images\\instructions_button.png";
const char LEAD_BTN[] = "images\\leaderboards_button.png";
const char MENU_BG[] = "images\\menu_bg.png";
const char INS_BG[] = "images\\instructions_Bg.png";
const char BACK_BTN[] = "images\\back_button.png";
const char CREDITS_BG[] = "images\\credits_bg.png";
const char START_SCRN[] = "images\\start_screen.png";


// HUD
const char FONT_IMAGE[] = "images\\kongtext.png";
const char BAR_IMAGE[] = "images\\healthbar.png";
const char SMALLBOX_IMAGE[] = "images\\smallbox.png";
const char MEDIUMBOX_IMAGE[] = "images\\mediumbox.png";
const char LARGEBOX_IMAGE[] = "images\\largebox.png";
const char SQUAREBOX_IMAGE[] = "images\\squarebox.png";
const char SMALLSQUAREBOX_IMAGE[] = "images\\smallsquarebox.png";
const char LARGESQUAREBOX_IMAGE[] = "images\\largesquarebox.png";
const char BACKGROUND_IMAGE[] = "images\\background.png";
const char TOOLTIPBOX_IMAGE[] = "images\\tooltipbox.png";

// Borders
const int N_BORDERS = 4;
const char RED_BORDER_FILE[] = "images\\42-3.png";
const char BLUE_BORDER_FILE[] = "images\\42-4.png";
const char GREEN_BORDER_FILE[] = "images\\42-5.png";
const char ORANGE_BORDER_FILE[] = "images\\42-6.png";
enum class BorderType { RED, BLUE, GREEN, ORANGE };

// Units
const int N_UNITS = 8;
const char BLUE_ARCHER_FILE[] = "images\\16-0-multiframe.png";
const char BLUE_SPEARMAN_FILE[] = "images\\16-1-multiframe.png";
const char BLUE_CAVALRY_FILE[] = "images\\16-3-multiframe.png";
const char BLUE_CASTLE_FILE[] = "images\\4-6.png";

const char RED_ARCHER_FILE[] = "images\\17-0-multiframe.png";
const char RED_SPEARMAN_FILE[] = "images\\17-1-multiframe.png";
const char RED_CAVALRY_FILE[] = "images\\17-3-multiframe.png";
const char RED_CASTLE_FILE[] = "images\\4-7.png";
enum class UnitType { ARCHER, SPEARMAN, CAVALRY, CASTLE };
enum class PlayerType { PLAYER, OPPONENT };

// Tiles
const int N_TILES = 22;
const char GRASS_FILE[] = "images\\0-3.png";
const char FOREST_FILE[] = "images\\0-4.png";
const char MOUNTAIN_FILE[] = "images\\1-3.png";
const char SETTLEMENT_FILE[] = "images\\3-0.png";
const char RUIN_FILE[] = "images\\4-0.png";
const char WATER_FILE[] = "images\\2-5.png";
const char FLAGNEUTRAL_FILE[] = "images\\6-3.png";
const char FLAGPLAYER_FILE[] = "images\\6-2.png";
const char FLAGENEMY_FILE[] = "images\\6-4.png";
const char SWORDBUFF_FILE[] = "images\\5-1.png";
const char TELEPORT_FILE[] = "images\\16-5.png";

//paths
const char PATH_FILE1[] = "images\\10-1.png";
const char PATH_FILE2[] = "images\\10-2.png";
const char PATH_FILE3[] = "images\\10-0.png";
const char PATH_FILE4[] = "images\\11-1.png";
const char PATH_FILE5[] = "images\\11-0.png";
const char PATH_FILE6[] = "images\\9-0.png";
const char PATH_FILE7[] = "images\\9-1.png";
const char PATH_FILE8[] = "images\\12-2.png";
const char PATH_FILE9[] = "images\\9-5.png";
const char PATH_FILE10[] = "images\\33-6.png";

//house 
const char HOUSE_FILE1[] = "images\\6-0.png";
enum class TileType {
	GRASS, FOREST, MOUNTAIN, SETTLEMENT, CASTLE, RUIN, WATER, SWORDBUFF, TELEPORT
	// If more next line
};


// All
const int N_IMAGES = N_TILES + N_UNITS + N_BORDERS;
static const char* IMAGE_FILES[] = {
	// Border
	RED_BORDER_FILE, BLUE_BORDER_FILE,
	GREEN_BORDER_FILE, ORANGE_BORDER_FILE,
	// Units
	BLUE_ARCHER_FILE, BLUE_SPEARMAN_FILE, BLUE_CAVALRY_FILE,
	BLUE_CASTLE_FILE,
	RED_ARCHER_FILE, RED_SPEARMAN_FILE, RED_CAVALRY_FILE,
	RED_CASTLE_FILE,
	// Tiles
	GRASS_FILE, FOREST_FILE, MOUNTAIN_FILE, SETTLEMENT_FILE,
	RUIN_FILE, WATER_FILE,
	
	//buffs
	FLAGNEUTRAL_FILE, FLAGPLAYER_FILE, 
	FLAGENEMY_FILE, SWORDBUFF_FILE,TELEPORT_FILE,

	//path tiles
	PATH_FILE1, // --- 23 //
	PATH_FILE2, // )
	PATH_FILE3, // (
	PATH_FILE4, // +
	PATH_FILE5, // I
	PATH_FILE6, // l-
	PATH_FILE7, // -l
	PATH_FILE8, // J
	PATH_FILE9, // _l_
	PATH_FILE10,

	HOUSE_FILE1,

};

enum class ImageType {
	// Border
	RED_BORDER, BLUE_BORDER, GREEN_BORDER, ORANGE_BORDER,
	// Unit
	BLUE_ARCHER_UNIT, BLUE_SPEARMAN_UNIT, BLUE_CAVALRY_UNIT,
	BLUE_CASTLE_UNIT,
	RED_ARCHER_UNIT, RED_SPEARMAN_UNIT, RED_CAVALRY_UNIT,
	RED_CASTLE_UNIT,
	// Tiles
	GRASS_TILE, FOREST_TILE, MOUNTAIN_TILE, SETTLEMENT_TILE, 
	RUIN_TILE, WATER_TILE, SWORD_TILE, TELEPORT_TILE
};

// Level
#include <map>
const std::map<ImageType, int> IMAGE_MAP {
	{ImageType::RED_BORDER, 0},
	{ImageType::BLUE_BORDER, 1},
	{ImageType::GREEN_BORDER, 2},
	{ImageType::ORANGE_BORDER, 3},
	{ImageType::BLUE_ARCHER_UNIT, 4},
	{ImageType::BLUE_SPEARMAN_UNIT, 5},
	{ImageType::BLUE_CAVALRY_UNIT, 6},
	{ImageType::BLUE_CASTLE_UNIT, 7},
	{ImageType::RED_ARCHER_UNIT, 8},
	{ImageType::RED_SPEARMAN_UNIT, 9},
	{ImageType::RED_CAVALRY_UNIT, 10},
	{ImageType::RED_CASTLE_UNIT, 11},
	{ImageType::GRASS_TILE, 12},
	{ImageType::FOREST_TILE, 13},
	{ImageType::MOUNTAIN_TILE, 14},
	{ImageType::SETTLEMENT_TILE, 15},
	{ImageType::RUIN_TILE, 16},
	{ImageType::WATER_TILE, 17},
	{ImageType::SWORD_TILE, 18},
	{ImageType::TELEPORT_TILE, 19}
};

const int N_ROWS = 8;
const int N_COLS = 8;
const int IMAGE_WIDTH = 16;
const int IMAGE_HEIGHT = 16;
enum class GameState { PLAYING, LOSE, WIN, HIGHSCORE };
const int N_HIGHSCORES = 10;
const char SCORES_FILE[] = "game\\scores.txt";

// Standard Coord
class CoordF
{
public:
	float x, y;
	CoordF()					{ CoordF::x = 0; CoordF::y = 0; }
	CoordF(float x, float y)	{ CoordF::x = x; CoordF::y = y; }
};

class CoordI
{
public:
	int x, y;
	CoordI()				{ CoordI::x = 0; CoordI::y = 0; }
	CoordI(int x, int y)	{ CoordI::x = x; CoordI::y = y; }
};
