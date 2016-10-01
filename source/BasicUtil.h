#ifndef BasicUtil_h
#define BasicUtil_h

#include "Windows.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

enum ClickType 		{Left, Right, Middle};
enum ClickMode 		{Revert, Stay};

class ScreenGrabber
{
	HDC hdcScreen;
	HDC hdcCom;
	
	BITMAPINFOHEADER bih;
	
	int x;
	int y;
	int width;
	int height;
	
	
	public:
	byte* ScreenData;
	
	ScreenGrabber(int x, int y, int width, int height);
	~ScreenGrabber();
	
	bool UpdateScreen();
	
	int GetIndex(int x, int y);
	void GetColor(int x, int y, byte* color);
};

class ScreenInputter
{
	int screenWidth; 
	int screenHeight;
	
	double screenWidthRatio; 
	double screenHeightRatio; 
	
	ClickMode clickMode;
	
	void Mov(int x, int y);
	
	public:
	
	ScreenInputter(ClickMode mode);
	
	void SetClickMode(ClickMode mode);
	
	void Move(int x, int y);
	void Click(ClickType type);
	void Click(ClickType type, int x, int y);
	void Delay(int milliseconds);
};

#endif