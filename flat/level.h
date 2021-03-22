#pragma once
#define WIN32_LEAN_AND_MEAN

#include <map>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>
#include <limits>
#include <fstream>
#include <assert.h> 
#include <math.h> 
#include <time.h>

#include "constants.h"
#include "page.h"
#include "tile.h"
#include "unit.h"
#include "border.h"
#include "image.h"
#include "hud.h"
#include "audio.h"
#include "leaderboard.h"

using namespace std;

struct AnimationUnit {
    Unit* unit;
    float destinationX;
    float destinationY;
};

struct rAnimationUnit {
	Unit* unit;
	int originalX;
	int originalY;
	int attackX;
	int attackY;
};

class Level : public Page
{
private:
	// Units & Tiles
	Image images[N_IMAGES];
	Tile tileGrid[N_ROWS][N_COLS];
	Unit* unitGrid[N_ROWS][N_COLS];
	vector<Unit*> playerUnits;
	vector<Unit*> opponentUnits;
    vector<Unit*>* turnOpponentVector;
	Border border;
	Unit* playerCastle;
	Unit* opponentCastle;
	vector<pair<int, Unit*>> buffUnits;
	// HUD
	HUD* hud;
	SpriteText* spriteText;
	SpriteData unitSD;
	CoordF centerPlayfield;
	// Active Unit
	Unit* activeUnit;
    Unit* opponentUnit;
    vector<AnimationUnit> animationQueue;
	list<CoordI>* moveSquares;
	list<CoordI>* attackSquares;
	// Turn
	int turn;
	int currency;
	int aiCurrency;
	// Purchase Units
	Unit* placeholderUnit;
    bool purchasing;
    bool unitMoving;
    bool aiRan;
	// Camera
	float camX;
	float camY;
	float camScale;
	float camMoveSpeed;
	float camZoomSpeed;
	float stepX;
	float stepY;
	int originalVec;
	// End Game / Leaderboard
	GameState gameState;
	int score;
	int buff;
	int noCaptured;
	int control;
	string name;
	// ???
	float posX;
	float posY;
	float scale;
	map <int, TileType> mapTile;
	map <int, UnitType> unitTile;
    float timer;

	int lalalalalala;

public:
	Level();
	~Level();
	void releaseAll();
	void resetAll();
	void initialize(Graphics* graphics, Input* input, int a);
	void start();
	PageType update(float frameTime);
	void render();

	void drawUnits();
	void drawTiles(Tile tileGrid[N_ROWS][N_COLS]);
	inline CoordF gridToScreen(float x, float y);
	inline CoordF screenToGrid(int x, int y);

    bool animate(float frameTime);
    bool areSameFloat(float a, float b) { return fabs(a - b) < FLT_EPSILON; };
    bool positionInRange(list<CoordI>* positions, float gridX, float gridY);
	
	//coords read from files
	int textTileGrid[N_ROWS][N_COLS];
    int textUnitGrid[N_ROWS][N_COLS];
	
	int miniGrid[N_ROWS][N_COLS];
	RECT rect;
	//For storage of multiple levels
	//need to add checking
	void readFromFile(std::string mapString, int grid1[N_ROWS][N_COLS], int level);
	void drawMiniMap(Tile tileGrid[N_ROWS][N_COLS], float scale, float posX, float posY, Graphics* graphics, int miniGrid[N_ROWS][N_COLS]);
	bool check(SpriteData sd);
	void getCoordsMini(SpriteData & sd,int x, int y, int size, float posX, float posY);
	void getCoordsMiniGrid(SpriteData& sd, int size, float posX, float posY);
	void createRect(float posX, float posY, float scale, RECT& rect);
	void drawMapBorder(int r, int c, SpriteData sd, int scale);
	void drawBorderLine();
    bool checkGameTurn();
    void checkGameEnd();
    void clickCastle(float gridX, float gridY);
    void endTurn();
    void resetUnitPhase();
    void resetBorders();
    void clickMinimap(float frameTime, int mouseX, int mouseY);
    void updateSpriteAnimation(float frameTime);
    void setPlaceholderUnit();
    void updatePlaceholderUnitPosition(int mouseX, int mouseY);
    void updateTileEffects();

	// Borders (Move & Attack Squares)
	void drawBorders(list<CoordI>* positions, BorderType borderType);
	list<CoordI>* getMoveSquares(Unit* unit);
	list<CoordI>* getAttackSquares(Unit* unit);
	inline void _getMoveSquaresCheckUpdateGrid(
		int(&grid)[N_ROWS][N_COLS], list<CoordI>* checkSquares,
		int n, int y, int x);

	// AI
	void ai(PlayerType playerType);
	inline CoordF _aiGetAvPos(vector<Unit*>* units);
	inline void _aiMoveUnit(Unit* unit, int x, int y);
	inline float _aiDistBetw(float x1, float y1, float x2, float y2);
	inline void _aiAddUnit(int x, int y, vector<Unit*>* units, UnitType unitType, PlayerType playerType);
	int _aiUnitImageIndex(UnitType unitType, PlayerType playerType);
	//void _aiCopyUnits(vector<Unit*>* units, vector<Unit*>& unitsCopy, Unit* (&unitGridCopy)[N_ROWS][N_COLS]);
	// Leaderboard
	//void readScoresFile(vector<string>& names, vector<int>& scores);
	//void writeScoresFile(vector<string> &names, vector<int> &scores);
	//void addScoreToFile(string name, int score);
};
