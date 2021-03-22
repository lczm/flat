#include "unit.h"

Unit::Unit()
{
	health = 0;
	moveRange = 0;
	attackRange = 0;
	attackPower = 0;
	value = 0;
}

Unit::~Unit()
{}

void Unit::initialize(Image* image, UnitType unitType, PlayerType player)
{
	Entity::initialize(image);
    Unit::unit = unitType;
	Unit::player = player;
    Unit::moveSpeed = 10;
    Unit::movePhaseOver = false;
    Unit::attackPhaseOver = false;
	switch (unitType)
	{
	case UnitType::ARCHER:
		Unit::health = 10;
        Unit::currentHealth = 10;
		Unit::moveRange = 2;
		Unit::attackRange = 3;
		Unit::attackPower = 8;
		Unit::value = 2000;
		break;
	case UnitType::SPEARMAN:
		Unit::health = 15;
		Unit::currentHealth = 15;
		Unit::moveRange = 2;
		Unit::attackRange = 1;
		Unit::attackPower = 10;
		Unit::value = 1000;
		break;
    case UnitType::CAVALRY:
        Unit::health = 20;
        Unit::currentHealth = 20;
        Unit::moveRange = 3;
        Unit::attackRange = 2;
        Unit::attackPower = 15;
        Unit::value = 3000;
		break;
	case UnitType::CASTLE:
		Unit::health = 50;
		Unit::currentHealth = 50;
		Unit::moveRange = 0;
		Unit::attackRange = 0;
		Unit::attackPower = 0;
		Unit::value = 0;
		break;
	}
}

void Unit::move(float destinationX, float destinationY) {
    // movePhaseOver = true;
    //Unit::destinationX = floor(destinationX);
    //Unit::destinationY = floor(destinationY);
}

void Unit::attack(Unit* opponentUnit) {
    // attackPhaseOver = true;
    originalX = x;
    originalY = y;

    // destinationX = opponentUnit->getX();
    // destinationY = opponentUnit->getY();

    // Do health calculation
    opponentUnit->setCurrentHealth(opponentUnit->getCurrentHealth() - attackPower);
}