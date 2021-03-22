#pragma once
#define WIN_32_LEAN_AND_MEAN

#include "image.h"
class Entity
{
private:
	Image* image;
	int frameNo;
public:
	Entity();
	~Entity();
	virtual void initialize(Image* image);

	SpriteData getSpriteData() { return image->getSpriteData(frameNo); }
	int setFrameNo() { return frameNo; }
	int getFrameNo() { return frameNo; }
    void updateFrameNo() { frameNo = (frameNo + 1) % image->getCols(); }

	Image * getImage(){ return image; }
};