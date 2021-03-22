#include "image.h"

Image::Image()
{
    initialized = false;
    spriteData.width = 1;
    spriteData.height = 1;
    spriteData.x = 0.0;
    spriteData.y = 0.0;
    spriteData.scale = 1.0;
    spriteData.angle = 0.0;
    spriteData.rect.left = 0;
    spriteData.rect.top = 0;
    spriteData.rect.right = spriteData.width;
    spriteData.rect.bottom = spriteData.height;
    spriteData.texture = NULL;
    spriteData.flipHorizontal = false;
    spriteData.flipVertical = false;
	cols = 0;
}

Image::~Image()
{
	SAFE_RELEASE(spriteData.texture);
}

bool Image::initialize(Graphics* graphics, const char* file, int width, int height)
{
	Image::graphics = graphics;
	Image::file = file;
	try {
		HRESULT hr;
		UINT fullWidth, fullHeight;
		LP_TEXTURE texture;
		hr = graphics->loadTexture(file, TRANSCOLOR, fullWidth, fullHeight, texture);
		if (FAILED(hr)) {
			SAFE_RELEASE(texture);
			return false;
		}
		spriteData.texture = texture;
		if (width == 0)		width = fullWidth;
		if (height == 0)	height = fullHeight;
		spriteData.width = width;
		spriteData.height = height;
		Image::cols = fullWidth / width;
		setRect(0);
	}
	catch (...) {
		return false;
	}
	initialized = true;
	return true;
}

void Image::onLostDevice()
{
	if (!initialized) return;
	SAFE_RELEASE(spriteData.texture);
}

void Image::onResetDevice()
{
	UINT width, height;
	LP_TEXTURE texture;
	if (!initialized) return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
	spriteData.texture = texture;
	spriteData.width = width;
	spriteData.height = height;
}

inline void Image::setRect(int frameNo)
{
	spriteData.rect.left = (frameNo % cols) * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (frameNo / cols) * spriteData.height;
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}

SpriteData Image::getSpriteData(int frameNo)
{
	setRect(frameNo);
	return spriteData;
}
