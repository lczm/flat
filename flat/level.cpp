#include "level.h"

Level::Level()
{
	// Units
	playerCastle = NULL;
	opponentCastle = NULL;
	// HUD
	hud = new HUD();
	// Active Unit
	activeUnit = NULL;
	opponentUnit = NULL;
    turnOpponentVector = NULL;
	moveSquares = NULL;
	attackSquares = NULL;
	placeholderUnit = NULL;
	// Camera
	camX = 5;
	camY = 5;
	camScale = 3.5;
	camMoveSpeed = 20;
	camZoomSpeed = 2;
	// Turn
	score = 999;
    turn = 1;
	currency = 1000;
	aiCurrency = 0;
	gameState = GameState::PLAYING;
	// Purchase Units
    purchasing = false;
    aiRan = false;
	control = 0;
	noCaptured = 0;
	buff = 10;
	// Mini map positions
	posX = 20;
	posY = -20;
	scale = 0.8;

	//tile number - 12 will give u this number 
	//Eg, 0 for grass when grass is 12 in the text file

	mapTile[0] = TileType::GRASS;
	mapTile[1] = TileType::FOREST,
	mapTile[2] = TileType::MOUNTAIN,
	mapTile[3] = TileType::SETTLEMENT,
	//mapTile[4] = TileType::CASTLE,
	mapTile[5] = TileType::WATER;
	mapTile[9] = TileType::SWORDBUFF;
	mapTile[11] = TileType::TELEPORT;

    unitTile[7] = UnitType::CASTLE;
    unitTile[11] = UnitType::CASTLE;

    unitTile[4] = UnitType::ARCHER;
    unitTile[8] = UnitType::ARCHER;

    unitTile[6] = UnitType::CAVALRY;
    unitTile[10] = UnitType::CAVALRY;

    unitTile[5] = UnitType::SPEARMAN;
    unitTile[9] = UnitType::SPEARMAN;

	//creating the rect to store the coords of the mini-map
	createRect(posX, posY, scale, rect);

    float timer = 0;
}

Level::~Level()
{
	releaseAll();
	for (Unit* unit : playerUnits)			delete unit;
	for (Unit* unit : opponentUnits)		delete unit;
}

void Level::releaseAll()
{
	for (int i = 0; i < N_IMAGES; i++)
		images[i].onLostDevice();
}

void Level::resetAll()
{
	for (int i = 0; i < N_IMAGES; i++)
		images[i].onResetDevice();
}

void Level::initialize(Graphics* graphics, Input* input, int a)
{
	Page::initialize(graphics, input);

	// Init Images
	for (int i = 0; i < N_IMAGES; i++) 
		images[i].initialize(graphics, IMAGE_FILES[i], 16, 16);

	// Init Border
	border.initialize(images + 0, images + 1, images + 2, images + 3);

	//read from files
	//generic filename , grid , level

	if (a == 0) {
        /* Tutorial Map and Units */
        readFromFile("tutorialMap.txt", textTileGrid, 1);
        readFromFile("tutorialUnits.txt", textUnitGrid, 1);
		lalalalalala = 0;
	} 
	else if (a == 1) {
        /* Original map*/
        readFromFile("run.txt", textTileGrid, 1);
        readFromFile("unit.txt", textUnitGrid, 1);
		lalalalalala = 1;
	}

	// Init Tiles
	for (int r = 0; r < N_ROWS; r++) {
		for (int c = 0; c < N_COLS; c++) {
			if (textTileGrid[r][c] >= 0) {
				int mapTileptr = textTileGrid[r][c]- N_UNITS - N_BORDERS;
				//Assign its given role eg. settlement
				if (mapTileptr < 0 ) {	
					//give the tile grass
					tileGrid[r][c].initialize(images + textTileGrid[r][c], mapTile[0]);
				}
				else {	
					tileGrid[r][c].initialize(images + textTileGrid[r][c], mapTile[mapTileptr]);
					if (tileGrid[r][c].getResistance() <= 0)
					{	
						//set minimum resistance
						tileGrid[r][c].setResistance(1);
					}
				}
			}
		}
	}

    for (int r = 0; r < N_ROWS; r++) {
        for (int c = 0; c < N_COLS; c++) {
            if (textUnitGrid[r][c] > 0) {
                if (textUnitGrid[r][c] <= 7) {
                    Unit* unit = new Unit();
                    unit->initialize(images + textUnitGrid[r][c], unitTile[textUnitGrid[r][c]], PlayerType::PLAYER);
                    unitGrid[r][c] = unit;
                    playerUnits.push_back(unitGrid[r][c]);
					if (textUnitGrid[r][c] == 7) {
						playerCastle = unit;
					}
                }
                else {
                    Unit* unit = new Unit();
                    unit->initialize(images + textUnitGrid[r][c], unitTile[textUnitGrid[r][c]], PlayerType::OPPONENT);
                    unitGrid[r][c] = unit;
                    opponentUnits.push_back(unitGrid[r][c]);
					if (textUnitGrid[r][c] == 11) {
						opponentCastle = unit;
					}
                }
                unitGrid[r][c]->setPos(c, r);
            }
            else {
                unitGrid[r][c] = NULL;
            }
        }
    }

	// initialize HUD
	hud->initialize(graphics, input);
}

void Level::start()
{}

PageType Level::update(float frameTime)
{
    checkGameEnd();
    // Setting turnOpponentVector
	if (turn % 2 == 1) turnOpponentVector = &opponentUnits;
	else if (turn % 2 == 0) turnOpponentVector = &playerUnits;

    // Camera input checking
    if (input->isKeyDown(VK_LEFT))      camX -= camMoveSpeed * frameTime;
	if (input->isKeyDown(VK_RIGHT))     camX += camMoveSpeed * frameTime;
	if (input->isKeyDown(VK_UP))        camY -= camMoveSpeed * frameTime;
	if (input->isKeyDown(VK_DOWN))      camY += camMoveSpeed * frameTime;
	if (input->isKeyDown(0x50))         camScale += camZoomSpeed * frameTime;
	if (input->isKeyDown(0x4F))         camScale -= camZoomSpeed * frameTime;
    if (input->isKeyDown(VK_ESCAPE)) {
        purchasing = false;
        delete moveSquares;
        moveSquares = NULL;
    }
	if (input->getMouseRButton())
	{
		if (input->getMouseX() > GAME_WIDTH - 10 && input->getMouseX() < GAME_WIDTH) camX += camMoveSpeed * frameTime;
		if (input->getMouseX() < 0 +10  && input->getMouseX() > 0 ) camX -= camMoveSpeed * frameTime;
		if (input->getMouseY() > GAME_HEIGHT - 10 && input->getMouseY() < GAME_HEIGHT) camY += camMoveSpeed * frameTime;
		if (input->getMouseY() < 0 + 10 && input->getMouseY() > 0 ) camY -= camMoveSpeed * frameTime;
	}
	if (camScale>= 9) camScale = 9;
	if (input->isKeyDown(0x57))			opponentCastle->setCurrentHealth(0);

    // Multi-frame Animation
    updateSpriteAnimation(frameTime);
	
	// Getting points of upper and lower grid
	// A coords =	 (0,0)
	// Z coords =     (15,15)
	CoordF pointA = gridToScreen(N_COLS-N_COLS,N_ROWS-N_ROWS);
	CoordF pointZ = gridToScreen(N_COLS-1, N_ROWS-1);

	// center of playfield coordinates
	centerPlayfield = gridToScreen(0, 0);

	// First coord x - camX + half the number of tiles in the map
	if (pointA.x > GAME_WIDTH) camX = 0 - camX + N_ROWS/2;
	if (pointZ.x < 0) camX = (N_ROWS-1) - camX + N_ROWS/2;
	if (pointA.y > GAME_HEIGHT) camY = 0 - camY + N_COLS/2;
	if (pointZ.y < 0) camY = (N_COLS - 1) - camY + N_COLS/2;
	
    if (placeholderUnit) updatePlaceholderUnitPosition(input->getMouseX(), input->getMouseY());

    // If the Left Mouse Button gets clicked on
    if (input->getMouseLButton()) {
        int mouseX = input->getMouseX();
        int mouseY = input->getMouseY();

        CoordF point = screenToGrid(mouseX, mouseY);
        float gridX = point.x;
        float gridY = point.y;

        input->setMouseLButton(false);

        clickMinimap(frameTime, mouseX, mouseY); // Check if clicking on the minimap
        clickCastle(gridX, gridY);               // Check if clicking on the castle

		if (hud->exitClick(mouseX, mouseY)) {
			return PageType::MAIN_MENU;
		}
        // Shop Menus, Next Page, Prev Page
        if (purchasing && hud->nextPageClick(mouseX, mouseY)) hud->nextPage();
        if (purchasing && hud->prevPageClick(mouseX, mouseY)) hud->prevPage();
		if (purchasing && hud->closeShopClick(mouseX, mouseY)) purchasing = false;
        if (hud->magnifyMapClick(mouseX, mouseY)) camScale += 0.5;
        if (hud->minifyMapClick(mouseX, mouseY)) camScale -= 0.5;
        if (animationQueue.size() == 0 && hud->endButtonClick(mouseX, mouseY)) {
            endTurn();
            aiRan = false;
            if (lalalalalala == 0) return PageType::TUTORIAL;
            else if (lalalalalala == 1) return PageType::LEVEL;
        }

        // When a placeholderUnit is already defined, try to place it, but check
        // for conditions; currency, location
        if (purchasing && hud->buyUnitClick(mouseX, mouseY)) {
            setPlaceholderUnit();
            if (lalalalalala == 0) return PageType::TUTORIAL;
            else if (lalalalalala == 1) return PageType::LEVEL;
        }
        else if (placeholderUnit &&
            (int)(gridX) >= 0 && (int)(gridX) < N_ROWS &&
            (int)(gridY) >= 0 && (int)(gridY) < N_COLS &&
            currency >= placeholderUnit->getValue() &&
            !unitGrid[(int)placeholderUnit->getY()][(int)placeholderUnit->getX()] &&
            ((areSameFloat(placeholderUnit->getX(), playerCastle->getX() + 1) && areSameFloat(placeholderUnit->getY(), playerCastle->getY())) ||
            (areSameFloat(placeholderUnit->getX(), playerCastle->getX() - 1) && areSameFloat(placeholderUnit->getY(), playerCastle->getY())) ||
            (areSameFloat(placeholderUnit->getX(), playerCastle->getX()) && areSameFloat(placeholderUnit->getY(), playerCastle->getY() - 1)) ||
            (areSameFloat(placeholderUnit->getX(), playerCastle->getX()) && areSameFloat(placeholderUnit->getY(), playerCastle->getY() + 1)))) {
            // update unitGrid && playerUnits && reset placeholderUnit
            currency -= placeholderUnit->getValue();
            unitGrid[(int)placeholderUnit->getY()][(int)placeholderUnit->getX()] = placeholderUnit;
            playerUnits.push_back(placeholderUnit);
            placeholderUnit = NULL;
            activeUnit = NULL;
            purchasing = false;
            moveSquares = NULL;
            if (lalalalalala == 0) return PageType::TUTORIAL;
            else if (lalalalalala == 1) return PageType::LEVEL;
        }
        else if (placeholderUnit && currency < placeholderUnit->getValue()) {
			hud->setTooltipText("Not enough gold!");
            placeholderUnit = NULL;
            activeUnit = NULL;
            purchasing = false;
            if (lalalalalala == 0) return PageType::TUTORIAL;
            else if (lalalalalala == 1) return PageType::LEVEL;
        }

        // If they click out the grid bounds
		if (gridX < 0 || gridY < 0) {
            if (lalalalalala == 0) return PageType::TUTORIAL;
            else if (lalalalalala == 1) return PageType::LEVEL;
		}

        // If there is not a unit selected
        if (!activeUnit && animationQueue.size() == 0) {
            for (int i = 0; i < playerUnits.size(); i++) {
                // Check if the gridX and gridY correspond to the unit's X and Y 
                // if ((int)gridX == entityVector[i]->getX() && (int)gridY == entityVector[i]->getY()) {
                if (areSameFloat(floor(gridX), playerUnits[i]->getX()) &&
                    areSameFloat(floor(gridY), playerUnits[i]->getY()) &&
                    playerUnits[i]->getUnitType() != UnitType::CASTLE &&
                    (!playerUnits[i]->getAttackPhaseOver() ||
                     !playerUnits[i]->getMovePhaseOver())) {
                    activeUnit = playerUnits[i];
                    // If the unit can be found on where the user clicks
                    // Check if the movePhase of the unit is over, if it is not, show movement squares
                    // Check if the attackPhase of the unit is over, if it is not, show attack squares
                    if (!activeUnit->getMovePhaseOver()) moveSquares = getMoveSquares(activeUnit);
                    else if (!activeUnit->getAttackPhaseOver()) attackSquares = getAttackSquares(activeUnit);
                }
            }
        }
        // If a unit is selected
        else if (activeUnit) {
            // If the player clicks at the same spot of the user : Wait at the same spot
            // Set the movePhase to be over, as the unit 'Waited'
            if (areSameFloat(activeUnit->getX(), floor(gridX)) && areSameFloat(activeUnit->getY(), floor(gridY))) {
                delete moveSquares;
                moveSquares = NULL;

                if (!activeUnit->getMovePhaseOver()) {
                    // activeUnit->move(gridX, gridY);
                    animationQueue.push_back(AnimationUnit{ activeUnit, floor(gridX), floor(gridY) });
                } 
                else if (activeUnit->getMovePhaseOver() && !activeUnit->getAttackPhaseOver()) {
                    activeUnit->setAttackPhaseOver(true);
                    activeUnit = NULL;
                    delete attackSquares;
                    attackSquares = NULL;
                }
            }
            // Try to move to the location that is being pointed; movePhase
            else if (!activeUnit->getMovePhaseOver() && positionInRange(moveSquares, floor(gridX), floor(gridY))) {
                // Remove moveSquares when the unit starts moving
                delete moveSquares;
                moveSquares = NULL;

                // Move the unit
                // activeUnit->move(gridX, gridY);
                animationQueue.push_back(AnimationUnit{ activeUnit, floor(gridX), floor(gridY) });

                // update unitGrid
                unitGrid[(int)activeUnit->getY()][(int)activeUnit->getX()] = NULL;
                unitGrid[(int)floor(gridY)][(int)floor(gridX)] = activeUnit;
            }
            // Try to attack the location that is being pointed; attackPhase
            else if (!activeUnit->getAttackPhaseOver() && positionInRange(attackSquares, gridX, gridY)) {
                // Get opponentUnit
                for (int i = 0; i < opponentUnits.size(); i++) {
                    if (areSameFloat(floor(gridX), opponentUnits[i]->getX()) &&
                        areSameFloat(floor(gridY), opponentUnits[i]->getY())) {
                        opponentUnit = opponentUnits[i];
                        activeUnit->attack(opponentUnit);
                        animationQueue.push_back(AnimationUnit{ activeUnit, floor(gridX), floor(gridY) });
                        // Remove attackSquares when the unit starts attacking
                        delete attackSquares;
                        attackSquares = NULL;
                        opponentUnit = NULL;
                    }
                }
            }
        }
		// iop
		if (gameState != GameState::PLAYING) {
			if (hud->endBtnClick()) {
				if (gameState == GameState::HIGHSCORE) {
					Leaderboard::addScoreToFile(name, score);
					//addScoreToFile(name, score);
					int x = 0;
					return PageType::LEADERBOARD;
				}
				else {
					return PageType::LEADERBOARD;
				}
			}
		}
    }

	if (gameState == GameState::HIGHSCORE) {
		name = input->getTextIn();
		if (input->getCharIn() == '\r')
			input->clearTextIn();
	}
	
    updateTileEffects();

    if (!animationQueue.empty()) {
        animate(frameTime);
        if (lalalalalala == 0) return PageType::TUTORIAL;
        else if (lalalalalala == 1) return PageType::LEVEL;
    }

    // If it is player's turn and they have no more moves to make
    // add currency to the ai, increment turn
    if (turn % 2 == 1 && checkGameTurn()) {
		// 1 Because the castle exists
		if (playerUnits.size() != 1) {
            aiCurrency += rand() % 1000;
            turn++;
            aiRan = false;
		}
    }
    else if (turn % 2 == 0) {
        if (!aiRan) {
            ai(PlayerType::OPPONENT);
            aiRan = true;
        }
        else {
            while (!animationQueue.empty()) {
                animate(frameTime);
            }
            currency += 2000;
            endTurn();
        }
		//checking and removing of buff code
		for (auto i = 0; i < buffUnits.size(); i++) {
			if (buffUnits[i].first == 0) {
				int current = buffUnits[i].second->getAttackPower();
				buffUnits[i].second->setAttackPower(current - buff);
				buffUnits[i].second->buff = false;
				buffUnits.erase(buffUnits.begin() + i);
			}
			else {
				buffUnits[i].first -= 1;
			}
		}

		if (control == 1)
			currency += 1000 - (noCaptured * 100);
		if (control == -1)
			aiCurrency += 1000 - (noCaptured * 100);
		control = 0;
    }

	if (lalalalalala == 0) return PageType::TUTORIAL;
	else if (lalalalalala == 1) return PageType::LEVEL;
}

bool Level::animate(float frameTime)
{
    AnimationUnit aUnit = animationQueue.front();
    Unit* unit = aUnit.unit;
    float destX = aUnit.destinationX;
    float destY = aUnit.destinationY;

    float moveDistance = frameTime * unit->getMoveSpeed();
	CoordF pos = gridToScreen(destX, destY);

    if (!areSameFloat(unit->getX(), destX)) {
        if (destX > unit->getX()) {
            if (unit->getX() + moveDistance > destX) {
                unit->setX(destX);
            } else {
                unit->setX(unit->getX() + moveDistance);
            }
        }
        else if (destX < unit->getX()) {
            if (unit->getX() + moveDistance < destX) {
                unit->setX(destX);
            } else {
                unit->setX(unit->getX() - moveDistance);
            }
        }
        return false;
    }

    if (!areSameFloat(unit->getY(), destY)) {
        if (destY > unit->getY()) {
            if (unit->getY() + moveDistance > destY) {
                unit->setY(destY);
            } else {
                unit->setY(unit->getY() + moveDistance);
            }
        }
        else if (destY < unit->getY()) {
            if (unit->getY() + moveDistance < destY) {
                unit->setY(destY);
            } else {
                unit->setY(unit->getY() - moveDistance);
            }
        }
        return false;
    }


    // Unit has reached its destination, if movePhase is not over, set it to true
    if (!unit->getMovePhaseOver()) {
        unit->setMovePhaseOver(true);
        // Show attacksquares, if its == 0 (nothing to attack), set attackPhase to be over
        if (turn % 2 == 1) {
            attackSquares = getAttackSquares(unit);
            if (attackSquares->size() == 0) {
                unit->setAttackPhaseOver(true);
            }
        }
    }
    // Unit has reached its destination, if movePhase is over, this will check for attackPhase
    // Because ^activeUnit->attack() sets for destination[X&Y], for it to reach this piece of code
    // it needs to have reached its destination. Which in this case is "The enemy position"
    // Once that happens, you can check if the enemy health is 0, as the deduction already happened in
    // activeUnit->attack()
    // Set the destination[X&Y] to the original[X&Y] => Move the unit back to the original location
    // unitMoving = true, to set the unit to move again
    // Check if current[X&Y] is the same as original[X&Y], if it is, it has finished moving back to the
    // original location. Hence attackPhase is over.
    else if (unit->getMovePhaseOver() && !unit->getAttackPhaseOver()) {
		hud->toggleShowDamageIndicator();
        turnOpponentVector;
        for (int i = 0; i < turnOpponentVector->size(); i++) {
            if (turnOpponentVector->at(i)->getCurrentHealth() == 0) {
				// Add to Score
                score += turnOpponentVector->at(i)->getValue();
                unitGrid[(int)turnOpponentVector->at(i)->getY()][(int)turnOpponentVector->at(i)->getX()] = NULL;
				turnOpponentVector->erase(turnOpponentVector->begin() + i);
			}
		}
		hud->setAttackedUnitXY(pos.x, pos.y);
		hud->setAttackingUnitDmg(unit->getAttackPower());
        // Add another animation instruction to the queue to 'move back the unit'
        animationQueue.insert(animationQueue.begin() + 1, AnimationUnit{ unit, unit->getOriginalX(), unit->getOriginalY() });
        unit->setAttackPhaseOver(true);
    }

    // Check if both phases are over, if it is, the unit will have nothing more to do.
    if (unit->getMovePhaseOver() && unit->getAttackPhaseOver()) {
        activeUnit = NULL;
		hud->setTooltipText("Select a unit to move it or click on the castle\nto purchase a unit!");
    }

    // animationQueue.pop();
    animationQueue.erase(animationQueue.begin());
    return true;
}

bool Level::checkGameTurn()
{
    for (int i = 0; i < playerUnits.size(); i++) {
        if (!(playerUnits[i]->getUnitType() == UnitType::CASTLE) && 
            (!playerUnits[i]->getMovePhaseOver() || !playerUnits[i]->getAttackPhaseOver())) {
                return false;
        }
    }
    return true;
}

void Level::checkGameEnd()
{
	if (turn % 2) {
		if (opponentCastle->getCurrentHealth() <= 0) {
			if (gameState == GameState::PLAYING) {
				vector<string> names; vector<int> scores;
				Leaderboard::readScoresFile(names, scores);
				if (scores.size() < N_HIGHSCORES || score > scores.back()) {
					input->clearTextIn();
					gameState = GameState::HIGHSCORE;
				}
				else
					gameState = GameState::WIN;
			}
		}
	}
	else {
		if (playerCastle->getCurrentHealth() <= 0)
			gameState = GameState::LOSE;
	}
}

void Level::clickCastle(float gridX, float gridY)
{
    for (int i = 0; i < playerUnits.size(); i++) {
        if (playerUnits[i]->getUnitType() == UnitType::CASTLE) {
            if (playerUnits[i]->getX() == (int)gridX && playerUnits[i]->getY() == (int)gridY) {
                purchasing = true;
            }
        }
    }
}

void Level::resetUnitPhase()
{
    for (int i = 0; i < playerUnits.size(); i++) {
        playerUnits[i]->setMovePhaseOver(false);
        playerUnits[i]->setAttackPhaseOver(false);
    }
    for (int i = 0; i < opponentUnits.size(); i++) {
        opponentUnits[i]->setMovePhaseOver(false);
        opponentUnits[i]->setAttackPhaseOver(false);
    }
}

void Level::endTurn()
{
    resetBorders();
	resetUnitPhase();
    turn++;
}

void Level::resetBorders()
{
    delete moveSquares;
    moveSquares = NULL;
    delete attackSquares;
    attackSquares = NULL;
}

void Level::clickMinimap(float frameTime, int mouseX, int mouseY)
{
    if (mouseX >= rect.left && mouseX < rect.right && mouseY >= rect.top && mouseY < rect.bottom)
    {
        SpriteData sd;

        //setting the mouse coordinates
        sd.x = mouseX;
        sd.y = mouseY;

        int size = scale * IMAGE_WIDTH;
        getCoordsMiniGrid(sd, size, posX, posY);

        //reset coords
        camX = 5;
        camY = 5;

        //Calculate on screen coords
        CoordF point = gridToScreen(sd.x, sd.y);

        //set cam coords
        camX += point.x * frameTime;
        camY += point.y * frameTime;
    }
}

void Level::updateSpriteAnimation(float frameTime)
{
    int i;
    timer += frameTime;
    if (timer > 0.8) {
        timer = 0;
        for (i = 0; i < playerUnits.size(); i++) {
            playerUnits[i]->updateFrameNo();
        }
        for (i = 0; i < opponentUnits.size(); i++) {
            opponentUnits[i]->updateFrameNo();
        }
    }
}

void Level::updatePlaceholderUnitPosition(int mouseX, int mouseY)
{
    // resetBorders();
    // Floor here because the units should not be 'intersecting with other borders'
    // and only be in 1 border at a time
    CoordF point = screenToGrid(mouseX, mouseY);
    placeholderUnit->setX(floor(point.x));
    placeholderUnit->setY(floor(point.y));
}

void Level::setPlaceholderUnit()
{
    purchasing = false;
    placeholderUnit = new Unit();
	hud->setTooltipText("Place the unit by clicking on one of the\nhighlighted tiles.");
    switch (hud->buyUnit())
    {
    case UnitType::ARCHER:
        placeholderUnit->initialize(images + 4, UnitType::ARCHER, PlayerType::PLAYER);
        break;
    case UnitType::SPEARMAN:
        placeholderUnit->initialize(images + 5, UnitType::SPEARMAN, PlayerType::PLAYER);
        break;
    case UnitType::CAVALRY:
        placeholderUnit->initialize(images + 6, UnitType::CAVALRY, PlayerType::PLAYER);
        break;
    }
    // border movesquare for showing castle movement here
	moveSquares = new list<CoordI>();
	if (unitGrid[(int)playerCastle->getY() + 1][(int)playerCastle->getX()] == NULL)
		moveSquares->push_back(CoordI(playerCastle->getX(), playerCastle->getY() + 1));
	if (unitGrid[(int)playerCastle->getY() - 1][(int)playerCastle->getX()] == NULL)
		moveSquares->push_back(CoordI(playerCastle->getX(), playerCastle->getY() - 1));
	if (unitGrid[(int)playerCastle->getY()][(int)playerCastle->getX() - 1] == NULL)
		moveSquares->push_back(CoordI(playerCastle->getX() - 1, playerCastle->getY()));
	if (unitGrid[(int)playerCastle->getY()][(int)playerCastle->getX() + 1] == NULL)
		moveSquares->push_back(CoordI(playerCastle->getX() + 1, playerCastle->getY()));
}

void Level::updateTileEffects()
{
	//checking for any units on the tile
	for (int r = 0; r < N_ROWS; r++)
	{
		for (int c = 0; c < N_COLS; c++)
		{	
			//Attack buff
			if (tileGrid[r][c].getType() == TileType::SWORDBUFF)
			{	
				SpriteData sd = tileGrid[r][c].getSpriteData();

				//players
				for (Unit* unit : playerUnits)
				{
					if (unit->getX() == c && unit->getY() == r && unit->buff != true)
					{	
						unit->buff = true;
						int currentAttack = unit->getAttackPower();
						int buffedAttack = currentAttack + buff;
						unit->setAttackPower(buffedAttack);
						buffUnits.emplace_back(2, unit);

					}
				}

				//opponents
				for (Unit* unit : opponentUnits)
				{
					if (unit->getX() == c && unit->getY() == r && unit->buff != true)
					{
						unit->buff = true;
						int currentAttack = unit->getAttackPower();
						int buffedAttack = currentAttack + buff;
						unit->setAttackPower(buffedAttack);
						buffUnits.emplace_back(2, unit);

					}
				}
			}

			//Prototype Settlement control
			if (tileGrid[r][c].getType() == TileType::SETTLEMENT)
			{	
				//player units
				for (Unit* unit : playerUnits) {

					if (unit->getX() == c && unit->getY() == r)
					{
						if (control == 0 && control != -1) {
							control = 1;
							noCaptured += 1;
						}
					}
					
				}
				//opponent units
				for (Unit* unit : opponentUnits) {
					if (unit->getX() == c && unit->getY() == r) {
						if (control == 0 && control != 1) {
							control = -1;
							noCaptured += 1;
						}
					}
				}
			}
		}
	}
}

void Level::render()
{	
	//graphics->spriteBegin();
	drawBorderLine();
    // draw Tiles then Units
	hud->drawPlayfieldBackground(centerPlayfield.x, centerPlayfield.y, camScale);
	drawTiles(tileGrid);
	drawUnits();
	//drawing the mini-map
	hud->drawMinimapBorder();
	drawMiniMap(tileGrid, scale, posX, posY, graphics,miniGrid);
	hud->draw(std::to_string(turn), std::to_string(currency));

	//miniMap(houseGrid, 0.5, 0.8, 0.1, graphics,miniGrid);
    if (moveSquares)   drawBorders(moveSquares, BorderType::ORANGE);
	if (attackSquares) drawBorders(attackSquares, BorderType::RED);
	if (activeUnit) {
		hud->drawUnitInfo(
			activeUnit->getSpriteData(),
			activeUnit->getCurrentHealth(),
			activeUnit->getHealth(),
			std::to_string(activeUnit->getAttackPower()),
			std::to_string(activeUnit->getMoveRange()),
			activeUnit->buff
		);
	}
	if (purchasing) hud->drawShop();


	hud->damagePopUp(camScale);
	//drawing the mini-map
	drawMiniMap(tileGrid, scale, posX, posY, graphics,miniGrid);
	hud->draw(std::to_string(turn), std::to_string(currency));
	// Input Name for Leaderboard
	if (gameState != GameState::PLAYING) {
		switch (gameState) {
		case GameState::WIN:
			hud->drawEndBox("YOU WIN!", score, "", "Exit"); break;
		case GameState::LOSE:
			hud->drawEndBox("YOU LOST!", score, "", "Exit"); break;
		case GameState::HIGHSCORE:
			string displayName = name;
			displayName.resize(8, '_');
			hud->drawEndBox("HIGH SCORE!", score, displayName, "Submit"); break;
		}
	}
	//graphics->spriteEnd();
}

bool Level::positionInRange(list<CoordI>* positions, float gridX, float gridY) 
{
    if (!positions) return false;
    for (CoordI coord : *positions) {
        if ((int)gridX == coord.x && (int)gridY == coord.y) {
            return true;
        }
    }
    return false;
}

void Level::drawTiles(Tile tileGrid[N_ROWS][N_COLS])
{
	for (int r = 0; r < N_ROWS; r++) {
		for (int c = 0; c < N_COLS; c++) {
			//checking if the tile has been assigned the value of (-)
			if (!(tileGrid[r][c].getImage() == nullptr))
			{
				Tile tile = tileGrid[r][c];
				SpriteData sd = tile.getSpriteData();
				CoordF pos = gridToScreen(c, r);
				sd.scale = camScale;
				sd.x = pos.x;
				sd.y = pos.y;
				//to only render what the user is only seeing
				miniGrid[r][c] = 0;
				if (check(sd))
				{
					//drawMapBorder(r, c, sd, camScale);
					miniGrid[r][c] = -1;
					if (tile.getColor() != NULL)
					{
						graphics->drawSprite(sd, tile.getColor());
					}
					else {
						graphics->drawSprite(sd);
					}
				}
			}
		}
	}
}

void Level::drawUnits()
{
	for (Unit* unit : playerUnits) {
		SpriteData sd = unit->getSpriteData();
		CoordF pos = gridToScreen(unit->getX(), unit->getY());
		sd.scale = camScale;
		sd.x = pos.x;
		sd.y = pos.y;
		if (check(sd))
		{
            if (unit->getMovePhaseOver() && unit->getAttackPhaseOver()) graphics->drawSprite(sd, graphicsNS::LTGRAY);
            else graphics->drawSprite(sd);
			hud->drawUnitHPBar(sd.x, sd.y, sd.width, camScale, unit->getCurrentHealth(), unit->getHealth());
		}
	}
	for (Unit* unit : opponentUnits) {
		SpriteData sd = unit->getSpriteData();
		CoordF pos = gridToScreen(unit->getX(), unit->getY());
		_RPT1(0, "%f %f\n", unit->getX(), unit->getY());
		sd.scale = camScale;
		sd.x = pos.x;
		sd.y = pos.y;
		if (check(sd))
		{
			graphics->drawSprite(sd);
			hud->drawUnitHPBar(sd.x, sd.y, sd.width, camScale, unit->getCurrentHealth(), unit->getHealth());
		}
	}
    if (placeholderUnit) {
		SpriteData sd = placeholderUnit->getSpriteData();
		CoordF pos = gridToScreen(placeholderUnit->getX(), placeholderUnit->getY());
		sd.scale = camScale;
		sd.x = pos.x;
		sd.y = pos.y;
		if (check(sd))
		{
			graphics->drawSprite(sd);
		}
    }
}

void Level::drawBorders(list<CoordI>* squares, BorderType borderType)
{	
	//graphics->spriteBegin();
	SpriteData sd = border.getSpriteData(borderType);
	if (borderType == BorderType::ORANGE && activeUnit)
	{
		hud->setTooltipText("Move a unit by selecting the highlighted tiles\nor make the unit wait in place by clicking on\nthe unit itself.");
	}
	else if (borderType == BorderType::RED && activeUnit)
	{
		hud->setTooltipText("Attack the unit by clicking on the highlighted\nred tile or wait in place by clicking on the\nunit itself.");
	}
	for (CoordI coord : *squares) {
		CoordF pos = gridToScreen(coord.x, coord.y);
		sd.scale = camScale;
		sd.x = pos.x;
		sd.y = pos.y;
		if (check(sd))
		{
			graphics->drawSprite(sd);
		}
	}
	//graphics->spriteEnd();
}

inline CoordF Level::gridToScreen(float ax, float ay)
{
	// Relative Grid Coordinates

	//1. get the grid relative to what the camera sees
	//2. Get the number of blocks in the screen 
	//3. divide it by 2 to get the center of the screen 
	//4. divide it by the cam scale to get the centre of the screen when zoomed out / zoomed in
	//float gx = ax - camX + (GAME_WIDTH / IMAGE_WIDTH) / 2 / camScale;
	float gx = ax - camX + (GAME_WIDTH / IMAGE_WIDTH) / 2 / camScale;
	float gy = ay - camY + (GAME_HEIGHT / IMAGE_HEIGHT) / 2 / camScale;

	//1. Get the relative size of the image
	// Relative Screen Coordinates
	float sx = IMAGE_WIDTH * camScale * gx;
	float sy = IMAGE_HEIGHT * camScale * gy;

	return CoordF(sx, sy);
}

inline CoordF Level::screenToGrid(int sx, int sy)
{
	// Relative Grid Coordinates
	float rx = sx / IMAGE_WIDTH / camScale;
	float ry = sy / IMAGE_HEIGHT / camScale;

	// Absolute Grid Coordinates 
	float ax = rx + camX - (GAME_WIDTH / IMAGE_WIDTH) / 2 / camScale;
	float ay = ry + camY - (GAME_HEIGHT / IMAGE_HEIGHT) / 2 / camScale;

	return CoordF(ax, ay);
}

//Mini map
void Level::drawMiniMap(Tile tileGrid[N_ROWS][N_COLS], float scale, float posX, float posY, Graphics* graphics, int miniGrid[N_ROWS][N_COLS])
{	
	for (int r = 0; r < N_ROWS; r++) {
		for (int c = 0; c < N_COLS; c++) {
			int size = scale * IMAGE_WIDTH;
			if (!(tileGrid[r][c].getImage() == nullptr))
			{	
				Tile tile = tileGrid[r][c];
				SpriteData sd = tile.getSpriteData();
				getCoordsMini(sd, c, r, size, posX, posY);
				if (miniGrid[r][c] == -1)
				{
					graphics->drawSprite(sd);
				}
				else {
					//to add code later to show where your mouse is on the map
					graphics->drawSprite(sd, graphicsNS::GRAY);
				}
				/*
				if (tileGrid[r][c].border != NULL)
				{	
					drawMapBorder(r, c, sd, -1);
				}
				*/
			}
		}
	}

	//Placing the players/opponents onto the mini map
	int size = scale * IMAGE_WIDTH;
	for (int i = 0; i < playerUnits.size(); i++)
	{	
		int x = playerUnits[i]->getX();
		int y = playerUnits[i]->getY();
		SpriteData sd = playerUnits[i]->getSpriteData();
		getCoordsMini(sd, x, y, size, posX, posY);
		graphics->drawSprite(sd, graphicsNS::BLUE);
	}

	for (int i = 0; i < opponentUnits.size(); i++)
	{	
		int x = opponentUnits[i]->getX();
		int y = opponentUnits[i]->getY();
		
		SpriteData sd = opponentUnits[i]->getSpriteData();
		getCoordsMini(sd,x,y, size, posX, posY);
		graphics->drawSprite(sd, graphicsNS::RED);
	}
}

//get on screen miniMap coords
void Level::getCoordsMini(SpriteData & sd,int x, int y, int size, float posX, float posY) 
{
	sd.x = (((GAME_WIDTH / (N_ROWS * N_COLS)) - 1) / 5) + posX + x * size;
	sd.y = GAME_HEIGHT / IMAGE_HEIGHT - posY + y * size;
}

// get absolute coords from miniMap coords
void Level::getCoordsMiniGrid(SpriteData& sd,int size, float posX, float posY)
{	
	float x = ((sd.x - (((GAME_WIDTH / (N_ROWS * N_COLS)) - 1) / 5)) - posX) /size ;

	float y = ((sd.y - GAME_HEIGHT / IMAGE_HEIGHT) + posY) / size ;

	sd.x = x;
	sd.y = y;
}

//create an area for the user to click on
void Level::createRect(float posX, float posY, float scale, RECT & rect)
{	
	int size = scale * IMAGE_WIDTH;
	rect.left = (((GAME_WIDTH / (N_ROWS * N_COLS)) - 1) / 5) + posX + 0 * size;
	rect.top = GAME_HEIGHT / IMAGE_HEIGHT - posY + 0 * size;
	rect.right = (((GAME_WIDTH / (N_ROWS * N_COLS)) - 1) / 5) + posX + N_COLS * size;
	rect.bottom = GAME_HEIGHT / IMAGE_HEIGHT - posY + N_COLS * size;
}


//Check if the tile/Player is within the viewing range
bool Level::check(SpriteData sd)
{	
	if (sd.x < 0 - IMAGE_WIDTH* camScale)
		sd.x = -1;
	if (sd.x > GAME_WIDTH + IMAGE_WIDTH*camScale)
		sd.x = -1;
	if (sd.y > GAME_HEIGHT + IMAGE_HEIGHT*camScale)
		sd.y = -1;
	if (sd.y < 0 - IMAGE_HEIGHT*camScale)
		sd.y = -1;

	if (sd.x != -1 && sd.y != -1) {	
        return true;
	}
	return false;
}

//read from the txt file
void Level::readFromFile(std::string mapString, int grid1[N_ROWS][N_COLS], int level)
{
	std::ifstream file("text\\" + std::to_string(level) + mapString);
	for (int r = 0; r < N_ROWS; r++)
	{
		for (int c = 0; c < N_COLS; c++) {
			file >> grid1[r][c];
		}
	}
}

//border code
void Level::drawBorderLine()
{
	for (int r = 0; r < N_ROWS; r++)
	{
		for (int c = 0; c < N_COLS; c++)
		{
			if (r == N_ROWS - N_ROWS || r == N_ROWS || r == N_ROWS - 1)
				tileGrid[r][c].setBorder(true);
			if (r >= 0 && r <= N_ROWS)
				tileGrid[r][0].setBorder(true);
				tileGrid[r][N_COLS - 1].setBorder(true);
		}
	}
}

void Level::drawMapBorder(int r, int c, SpriteData sd, int scale)
{	

	//tile.setTile(images, 13, TileType::MOUNTAIN);


	int eqnX = IMAGE_WIDTH * scale;
	int eqnY = IMAGE_HEIGHT * scale;

	//checking if the map selected is a mini-map/MAP
	if (scale == -1)
	{
		eqnX = IMAGE_WIDTH;
		eqnY = IMAGE_HEIGHT;
	}

	if (r == N_ROWS - N_ROWS)
	{	
		sd.y = sd.y - eqnY;
		graphics->drawSprite(sd, graphicsNS::BLACK);
		sd.y = sd.y + eqnY;
	}
	
	if (r == N_ROWS - 1)
	{	
		sd.y = sd.y + eqnY;
		graphics->drawSprite(sd, graphicsNS::BLACK);
		sd.y = sd.y - eqnY;
	}
	if (r >= N_ROWS - N_ROWS && c == N_COLS - 1) {
		sd.x = sd.x + eqnX;
		graphics->drawSprite(sd, graphicsNS::BLACK);
		sd.x = sd.x - eqnX;


	}

	if (r >= N_ROWS - N_ROWS && c == N_COLS - N_COLS) {
		sd.x = sd.x - eqnX;
		graphics->drawSprite(sd, graphicsNS::BLACK);
		sd.x = sd.x + eqnX;
	}

	if (r == 0 && c == 0)
	{
		Tile tile;
		tile.initialize(images + 12, TileType::GRASS);
		SpriteData sds = tile.getSpriteData();
		sds = sd;
		sds.x = sd.y - eqnY -eqnY;
		sds.x = sd.x - eqnX;
		graphics->drawSprite(sds, graphicsNS::BLACK);
		sds.x = sd.x + eqnX;
	}
}

list<CoordI>* Level::getMoveSquares(Unit* unit)
{
	int n = unit->getMoveRange();
	int x = unit->getX(), y = unit->getY();
	int grid[N_ROWS][N_COLS];
	memset(grid, -1, N_ROWS * N_COLS * sizeof(int));
	list<CoordI>* checkSquares = new list<CoordI>();
	list<CoordI>* moveSquares = new list<CoordI>();
	grid[y][x] = n;
	checkSquares->push_back(CoordI(x, y));

	for (; n >= 0; n--) {
		list<CoordI>::iterator start = checkSquares->begin();
		list<CoordI>::iterator end = checkSquares->end();
		while (start != end) {
			int x = start->x, y = start->y;
			int moveRequired = grid[y][x];
			if (moveRequired >= n) {
				if (unitGrid[y][x] == NULL)
					moveSquares->push_back(CoordI(x, y));
				start = checkSquares->erase(start);
				if (y < N_ROWS - 1)	_getMoveSquaresCheckUpdateGrid(grid, checkSquares, n, y + 1, x);
				if (y > 0)			_getMoveSquaresCheckUpdateGrid(grid, checkSquares, n, y - 1, x);
				if (x > 0)			_getMoveSquaresCheckUpdateGrid(grid, checkSquares, n, y, x - 1);
				if (x < N_COLS - 1)	_getMoveSquaresCheckUpdateGrid(grid, checkSquares, n, y, x + 1);
			}
			else { start++; }
		}
	}

    moveSquares->push_back(CoordI(unit->getX(), unit->getY()));
	return moveSquares;
}

inline void Level::_getMoveSquaresCheckUpdateGrid(
	int(&grid)[N_ROWS][N_COLS], list<CoordI>* checkSquares,
	int n, int y, int x)
{
	if (grid[y][x] == -1) {
		if (tileGrid[y][x].getResistance() <= n) {
			checkSquares->push_back(CoordI(x, y));
			grid[y][x] = n - tileGrid[y][x].getResistance();
		}
		else { grid[y][x] = -2; }
	}
}

list<CoordI>* Level::getAttackSquares(Unit* unit)
{
	int n = unit->getAttackRange();
	const int maxAttackSquares = 2 * n * (n + 1);
	list<CoordI>* attackSquares = new list<CoordI>();
	vector<Unit*>* units = unit->getPlayerType() == PlayerType::OPPONENT ? &playerUnits : &opponentUnits;

	if (units->size() <= maxAttackSquares) {
		for (Unit* unit2 : *units) {
			if (unit2->getPlayerType() != unit->getPlayerType()) {
				int rangeRequired = abs(unit2->getX() - unit->getX()) + abs(unit2->getY() - unit->getY());
				if (rangeRequired <= n)
					attackSquares->push_back(CoordI(unit2->getX(), unit2->getY()));
			}
		}
	}
	else {
		// Top to Bottom
		for (int y = unit->getY() + n, yEnd = unit->getY() - n, i = -n; y >= yEnd; y--, i++) {
			int dx = n - abs(i);
			// Left to Right
			for (int x = unit->getX() - dx, xEnd = unit->getX() + dx; x <= xEnd; x++) {
				Unit* unit2 = unitGrid[y][x];
				if (unit2 != NULL && unit2->getPlayerType() != unit->getPlayerType())
					attackSquares->push_back(CoordI(x, y));
			}
		}
	}
	return attackSquares;
}

void Level::ai(PlayerType playerType)
{
	if (!(playerUnits.size() && opponentUnits.size())) return;

	vector<Unit*>* unitsA;
	vector<Unit*>* unitsB;

	Unit* castle;
	int archerIndex;
	if (playerType == PlayerType::PLAYER) {
		unitsA = &playerUnits;
		unitsB = &opponentUnits;
		castle = opponentCastle;
	}
	else {
		unitsA = &opponentUnits;
		unitsB = &playerUnits;
		castle = opponentCastle;
	}

	// Buy Units
	int castleX = (int)castle->getX();
	int castleY = (int)castle->getY();
	_aiAddUnit(castleX + 1, castleY, unitsA, UnitType::ARCHER, playerType);
	_aiAddUnit(castleX - 1, castleY, unitsA, UnitType::SPEARMAN, playerType);
	_aiAddUnit(castleX, castleY + 1, unitsA, UnitType::CAVALRY, playerType);
	_aiAddUnit(castleX, castleY - 1, unitsA, UnitType::ARCHER, playerType);

	// Get Average Units Position
	CoordF avAPos = _aiGetAvPos(unitsA);
	CoordF avBPos = _aiGetAvPos(unitsB);
	// Get Most Alone Unit B
	Unit* aloneUnitB = unitsB->front();
	float aloneDist = 0;
	for (Unit* unitB : *unitsB) {
		float dist = _aiDistBetw(unitB->getX(), unitB->getY(), avBPos.x, avBPos.y);
		if (dist > aloneDist) { aloneDist = dist; aloneUnitB = unitB; }
	}
	// Destination: Betw units A and alone unit B
	float destX = (avAPos.x + aloneUnitB->getX()) / 2;
	float destY = (avAPos.y + aloneUnitB->getY()) / 2;
	// If too near
	float distAwayB = _aiDistBetw(destX, destY, aloneUnitB->getX(), aloneUnitB->getY());
	if (distAwayB <= aloneUnitB->getAttackRange() + aloneUnitB->getMoveRange()) {
		// Destination: Attack unit B
		destX = aloneUnitB->getX(); destY = aloneUnitB->getY();
	}
	destX = floor(destX);
	destY = floor(destY);

	// AnimHack (Cache)
	stack<Unit*> deadUnits;
	stack<rAnimationUnit> animStack;

	// Move Units A
	for (Unit* unitA : *unitsA) {
		// AnimHack (Cache Unit)
		rAnimationUnit rAnimUnit {unitA, -1, -1, -1, -1};

		// Destination: Keep Distance (range unit)
		int backX = unitA->getX() - destX;
		int backY = unitA->getY() - destY;
		int backXY = abs(backX) + abs(backY);
		// if not at destination already
		if (backXY) {
			float ratioX = backX / backXY;
			float ratioY = backY / backXY;
			destX += round((unitA->getAttackRange() - 1) * ratioX);
			destY += round((unitA->getAttackRange() - 1) * ratioY);
		}

		// find nearest square
		list<CoordI>* moveSquares = getMoveSquares(unitA);
		CoordI nearSquare = CoordI(-1, -1);
		int nearDist = INT_MAX;
		for (CoordI moveSquare : *moveSquares) {
			int dist = _aiDistBetw(destX, destY, moveSquare.x, moveSquare.y);
			if (dist < nearDist) {
				nearDist = dist; nearSquare = moveSquare;
			}
		}
		delete moveSquares;
		// Move
		if (nearSquare.x != -1) {
			animationQueue.push_back(AnimationUnit{ unitA, (float)nearSquare.x, (float)nearSquare.y });
			unitGrid[(int)unitA->getY()][(int)unitA->getX()] = NULL;
			unitGrid[(int)nearSquare.y][(int)nearSquare.x] = unitA;
			rAnimUnit.originalX = unitA->getX();
			rAnimUnit.originalY = unitA->getY();
			unitA->setPos(nearSquare.x, nearSquare.y);
		}
		// find unit with lowest health
		list<CoordI>* attackSquares = getAttackSquares(unitA);
		CoordI lowSquare = CoordI(-1, -1);
		float lowHealth = INT_MAX;
		for (CoordI attackSquare : *attackSquares) {
			Unit* unitB = unitGrid[attackSquare.y][attackSquare.x];
			if (unitB->getCurrentHealth() < lowHealth) {
				lowHealth = unitB->getCurrentHealth(); lowSquare = attackSquare;
			}
		}
		delete attackSquares;
		// Attack
		if (lowSquare.x != -1) {
			Unit* unitB = unitGrid[lowSquare.y][lowSquare.x];
            animationQueue.push_back(AnimationUnit{ unitA, (float)lowSquare.x, (float)lowSquare.y });
			rAnimUnit.attackX = lowSquare.x;
			rAnimUnit.attackY = lowSquare.y;

			// Apparently animation does not take care of animation
			//unitB->setCurrentHealthForce(unitB->getCurrentHealth() - unitA->getAttackPower());
			unitA->attack(unitB);
			if (unitB->getCurrentHealth() <= 0) {
				for (vector<Unit*>::iterator start = unitsB->begin(), end = unitsB->end(); start != end; start++) {
					if (*start == unitB) {
						deadUnits.push(unitB);
						unitsB->erase(start);
						break;
					}
				}
				unitGrid[lowSquare.y][lowSquare.x] = NULL;
			}
			unitA->setDestinationPos(lowSquare.x, lowSquare.y);
		}

		// AnimHack (Push Unit)
		animStack.push(rAnimUnit);
	}

	// AnimHack (Rebuild)
	while (!animStack.empty()) {
		rAnimationUnit rAnimUnit = animStack.top();
		animStack.pop();
		Unit* unitA = rAnimUnit.unit;

		if (rAnimUnit.attackX != -1) {
			// UnAttack
			Unit* unitB = unitGrid[rAnimUnit.attackY][rAnimUnit.attackX];
			if (unitB == NULL) {
				unitB = deadUnits.top();
				deadUnits.pop();
				unitGrid[rAnimUnit.attackY][rAnimUnit.attackX] = unitB;
				unitsB->push_back(unitB);
			}
			// Apparently animation does not take care of damage but removal of units
			//unitB->setCurrentHealthForce(unitB->getCurrentHealth() + unitA->getAttackPower());
		}
		if (rAnimUnit.originalX != -1) {
			// UnMove
			// Moving from unitGrid not done by animation
			//unitGrid[(int)unitA->getY()][(int)unitA->getX()] = NULL;
			//unitGrid[rAnimUnit.originalY][rAnimUnit.originalX] = unitA;
			unitA->setPos(rAnimUnit.originalX, rAnimUnit.originalY);
		}
	}
}

inline CoordF Level::_aiGetAvPos(vector<Unit*>* units)
{
	float avX = 0;
	float avY = 0;
	for (Unit* unit : *units) { avX += unit->getX(); avY += unit->getY(); }
	avX /= units->size();
	avY /= units->size();
	return CoordF(avX, avY);
}

inline void Level::_aiMoveUnit(Unit* unit, int x, int y)
{
	assert(unitGrid[y][x] == NULL);
	unitGrid[(int)unit->getY()][(int)unit->getX()] = NULL;
	unitGrid[y][x] = unit;
	unit->setPos(x, y);
}

inline float Level::_aiDistBetw(float x1, float y1, float x2, float y2) {
	return fabs(x1 - x2) + fabs(y1 - y2);
}

inline void Level::_aiAddUnit(int x, int y, vector<Unit*>* units, UnitType unitType, PlayerType playerType)
{
	int imageIndex = _aiUnitImageIndex(unitType, playerType);
	if (unitGrid[y][x] == NULL) {
		Unit* unit = new Unit();
		unit->initialize(images + imageIndex, unitType, playerType);
		unit->setPos(x, y);
		if (aiCurrency < unit->getValue())
			delete unit;
		else {
			aiCurrency -= unit->getValue();
			unitGrid[y][x] = unit;
			units->push_back(unit);
		}
	}
}

int Level::_aiUnitImageIndex(UnitType unitType, PlayerType playerType)
{
	int imageIndex = -1;
	if (playerType == PlayerType::PLAYER) {
		switch (unitType) {
		case UnitType::SPEARMAN:
			imageIndex = IMAGE_MAP.at(ImageType::BLUE_SPEARMAN_UNIT); break;
		case UnitType::ARCHER:
			imageIndex = IMAGE_MAP.at(ImageType::BLUE_ARCHER_UNIT); break;
		case UnitType::CAVALRY:
			imageIndex = IMAGE_MAP.at(ImageType::BLUE_CAVALRY_UNIT); break;
		}
	}
	else {
		switch (unitType) {
		case UnitType::SPEARMAN:
			imageIndex = IMAGE_MAP.at(ImageType::RED_SPEARMAN_UNIT); break;
		case UnitType::ARCHER:
			imageIndex = IMAGE_MAP.at(ImageType::RED_ARCHER_UNIT); break;
		case UnitType::CAVALRY:
			imageIndex = IMAGE_MAP.at(ImageType::RED_CAVALRY_UNIT); break;
		}
	}
	return imageIndex;
}

//void Level::_aiCopyUnits(vector<Unit*>* units, vector<Unit*>& unitsCopy, Unit* (&unitGridCopy)[N_ROWS][N_COLS])
//{
//	for (Unit* unit : *units) {
//		Unit* newUnit = new Unit();
//		*newUnit = *unit;
//		unitsCopy.push_back(newUnit);
//		unitGridCopy[(int)newUnit->getY()][(int)newUnit->getX()] = newUnit;
//	}
//}