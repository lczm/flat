#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include "graphics.h"
#include "time.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"


class Game
{
protected:
    // common game properties
    Graphics* graphics;         // pointer to Graphics
    Input* input;             // pointer to Input
    HWND    hwnd;               // window handle
    HRESULT hr;                 // standard return type
    LARGE_INTEGER timeStart;    // Performance Counter start value
    LARGE_INTEGER timeEnd;      // Performance Counter end value
    LARGE_INTEGER timerFreq;    // Performance Counter frequency
    float   frameTime;          // time required for last frame
    float   fps;                // frames per second
    DWORD   sleepTime;          // number of milli-seconds to sleep between frames
    bool    paused;             // true if game is paused
    bool    initialized;

public:
    Game();
    virtual ~Game();
	virtual void initialize(HWND hwnd);
	virtual void releaseAll();
	virtual void resetAll();
	virtual void update() = 0;
	virtual void render() = 0;

    LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void run(HWND);
    virtual void deleteAll();
    virtual void renderGame();
    virtual void handleLostGraphicsDevice();
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

    Graphics* getGraphics() { return graphics; }
    Input* getInput() { return input; }
};
