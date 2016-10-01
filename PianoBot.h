#ifndef PianoBot_h
#define PianoBot_h

#define WindowCordX 2
#define WindowCordY 36
#define WindowWidth 480
#define WindowHeight 800

#define EndPixelX 98
#define EndPixelY 458
#define EndPixelR 94
#define EndPixelG 255
#define EndPixelB 158

#define EndPixelX_Safe 80
#define EndPixelY_Safe 437
#define EndPixelR_Safe 243
#define EndPixelG_Safe 123
#define EndPixelB_Safe 94

#define GAME "Piano Tiles two"
#define NUMBEROFTRACKS 4

#include "../../_BasicUtil/BasicUtil.h"

class PianoBot
{
	ScreenInputter inp = ScreenInputter(ClickMode::Stay);
	ScreenGrabber grb = ScreenGrabber(WindowCordX, WindowCordY, WindowWidth, WindowHeight);
	
	byte* colorTrigger;
	int* trackLocations;
	
	public:
	
	~PianoBot();
	PianoBot();
	
	void PrintStart();
	void Start();
	void PianoBot::WaitForInput();
};

#endif