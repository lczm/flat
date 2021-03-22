#include "entity.h"

Entity::Entity()
{
	image = NULL;
	frameNo = 0;
}

Entity::~Entity()
{}

void Entity::initialize(Image* image)
{
	Entity::image = image;
}