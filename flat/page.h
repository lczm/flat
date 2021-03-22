#pragma once
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"
#include "input.h"

class Page
{
protected:
	Graphics* graphics;
	Input* input;

public:
	Page();
	virtual ~Page();
	virtual void initialize(Graphics* graphics, Input* input);
	virtual void start();
	virtual void releaseAll();
	virtual void resetAll();
	virtual PageType update(float frameTime);
	virtual void render();

	Graphics* getGraphics() { return graphics; }
	Input* getInput() { return input; }
};