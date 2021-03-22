#pragma once
#define WIN32_LEAN_AND_MEAN

#include <fstream>
#include <vector>
#include "page.h"
#include "button.h"

using namespace std;

class Leaderboard : public Page
{
private:
	SpriteText spriteText;
	Image mainMenuBtnImage;
	Button mainMenuBtn;
	vector<string> names;
	vector<int> scores;

	int offsetX, offsetY;
	int titleSize, textSize;
	int textStepX;

public:
	Leaderboard();
	~Leaderboard();
	void initialize(Graphics* graphics, Input* input);
	void start();
	void releaseAll();
	void resetAll();
	PageType update(float frameTime);
	void render();

	// Leaderboard
	static void readScoresFile(vector<string>& names, vector<int>& scores);
	static void writeScoresFile(vector<string>& names, vector<int>& scores);
	static void addScoreToFile(string name, int score);
};