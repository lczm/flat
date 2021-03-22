#pragma once
#define WIN_32_LEAN_AND_MEAN

#include "entity.h"

class Unit : public Entity
{
private:
	PlayerType player;
	UnitType unit;
	int currentHealth;
	int health;
	int moveRange;
	int attackRange;
	int attackPower;
	int value;

	float x;
	float y;

	float moveSpeed;
	float destinationX;
	float destinationY;
	float originalX;
	float originalY;

	bool movePhaseOver;
	bool attackPhaseOver;
public:
	bool buff;
	Unit();
	~Unit();

    void setX(float x) { Unit::x = x; };
    float getX() { return x; };
    void setY(float y) { Unit::y = y; };
    float getY() { return y; };
	void setPos(float x, float y) { Unit::x = x; Unit::y = y; }

    void setCurrentHealth(int h) {
        if (h >= 0) {
            Unit::currentHealth = h;
        }
        else {
            Unit::currentHealth = 0;
        }
    }
	void setCurrentHealthForce(int h) { Unit::currentHealth = h; }
    int getCurrentHealth() { return currentHealth; }
    int getHealth() { return health; }

    int getMoveRange() { return moveRange; }
    int getAttackRange() { return attackRange; }
    int getAttackPower() { return attackPower; }
	void setAttackPower(int b) {Unit::attackPower = b; }

    PlayerType getPlayerType() { return Unit::player; }
    UnitType getUnitType() { return Unit::unit; }

	void initialize(Image* image, UnitType unitType, PlayerType player);

    void setMoveSpeed(float f) { Unit::moveSpeed = f; }
    float getMoveSpeed() { return moveSpeed; }

    void setDestinationX(float x) { Unit::destinationX = x; }
    float getDestinationX() { return destinationX; }

    void setDestinationY(float y) { Unit::destinationY = y; }
    float getDestinationY() { return destinationY; }

	void setDestinationPos(float x, float y) { Unit::destinationX = x; Unit::destinationY = y; }

    void setOriginalX(float x) { Unit::originalX = x; }
    float getOriginalX() { return originalX; }

    void setOriginalY(float y) { Unit::originalY = y; }
    float getOriginalY() { return originalY; }

	void setOriginalPos(float x, float y) { Unit::originalX = x; Unit::originalY = y; }

    void setMovePhaseOver(bool b) { Unit::movePhaseOver = b; }
    bool getMovePhaseOver() { return movePhaseOver; }

    void setAttackPhaseOver(bool b) { Unit::attackPhaseOver = b; }
    bool getAttackPhaseOver() { return attackPhaseOver; }

    void move(float destinationX, float destinationY);
    void attack(Unit* opponentUnit);
    int getValue() { return Unit::value; }
};