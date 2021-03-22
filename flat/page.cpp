#include "page.h"

Page::Page()
{}

Page::~Page()
{}

void Page::initialize(Graphics* graphics, Input* input)
{
	Page::graphics = graphics;
	Page::input = input;
}

void Page::start()
{}

void Page::releaseAll()
{}

void Page::resetAll()
{}

PageType Page::update(float frameTime)
{
	return PageType::MAIN_MENU;
}

void Page::render()
{}