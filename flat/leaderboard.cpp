#include "leaderboard.h"

Leaderboard::Leaderboard()
{
	offsetX = GAME_WIDTH / 2 + 30;
	offsetY = 180;

	titleSize = 60;
	textSize = 40;
	textStepX = 55;
}

Leaderboard::~Leaderboard()
{}

void Leaderboard::initialize(Graphics* graphics, Input* input)
{
	Page::initialize(graphics, input);
	if (!spriteText.initialize(graphics, FONT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the sprite text"));

	mainMenuBtnImage.initialize(graphics, "images\\mainmenubox.png");
	mainMenuBtn.initialize(
		graphics, input, &mainMenuBtnImage, &spriteText,
		PageType::MAIN_MENU, "MAIN MENU", 
		GAME_WIDTH - 400, GAME_HEIGHT - 100);
}

void Leaderboard::start()
{
	names.clear();
	scores.clear();
	readScoresFile(names, scores);
}

void Leaderboard::releaseAll()
{}

void Leaderboard::resetAll()
{}

PageType Leaderboard::update(float frameTime)
{
	if (mainMenuBtn.isClick())
		return PageType::MAIN_MENU;
	return PageType::LEADERBOARD;
}

void Leaderboard::render()
{
	spriteText.setFontHeight(titleSize);
	spriteText.print("LEADERBOARD", GAME_WIDTH / 2, GAME_HEIGHT / 15, textNS::CENTER);

	spriteText.setFontHeight(textSize);
	for (int i = 0; i < names.size(); i++) {
		string index = to_string(i + 1);
		index.resize(3, ' ');
		string name = names[i];
		name.resize(10, ' ');
		string score = to_string(scores[i]);
		score.resize(5, ' ');
		spriteText.print(index + name + score, 
			offsetX, i * textStepX + offsetY, textNS::CENTER);
	}

	mainMenuBtn.draw();
}

void Leaderboard::readScoresFile(vector<string>& names, vector<int>& scores)
{
	ifstream file(SCORES_FILE);
	string line;
	while (getline(file, line)) {
		string name = line;
		names.push_back(name);
		getline(file, line);
		int score = stoi(line);
		scores.push_back(score);
	}
}
void Leaderboard::writeScoresFile(vector<string>& names, vector<int>& scores)
{
	ofstream file(SCORES_FILE);
	for (int i = 0; i < names.size(); i++) {
		file << names[i] << "\n" << scores[i] << "\n";
	}
}
void Leaderboard::addScoreToFile(string name, int score)
{
	vector<string> names; vector<int> scores;
	readScoresFile(names, scores);
	int i = 0;
	for (; i < scores.size(); i++)
		if (score > scores[i]) break;
	names.emplace(names.begin() + i, name);
	scores.emplace(scores.begin() + i, score);
	names.resize(min(names.size(), N_HIGHSCORES));
	scores.resize(min(scores.size(), N_HIGHSCORES));
	writeScoresFile(names, scores);
}