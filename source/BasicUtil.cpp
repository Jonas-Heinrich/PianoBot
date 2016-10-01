#include "BasicUtil.h"

#include <iostream>
using namespace std;

//
//	ScreenGrabber
//

ScreenGrabber::ScreenGrabber(int x, int y, int width, int height)
{
	this->hdcScreen 		= GetDC(NULL);
	this->hdcCom 			= CreateCompatibleDC(hdcScreen);
	
    this->bih 				= {0};
    this->bih.biSize 		= sizeof(BITMAPINFOHEADER);
    this->bih.biPlanes 		= 1;
    this->bih.biBitCount 	= 32;
    this->bih.biWidth 		= width;
    this->bih.biHeight 		= -height;
    this->bih.biCompression	= BI_RGB;
    this->bih.biSizeImage 	= 0;
	
	this->x 				= x;
	this->y 				= y;
	this->width 			= width;
	this->height 			= height;
	
	this->ScreenData = NULL;
}

ScreenGrabber::~ScreenGrabber()
{
	if(ScreenData)
		free(ScreenData);
	ReleaseDC(NULL, hdcScreen);
	DeleteDC(hdcCom);
}

bool ScreenGrabber::UpdateScreen()
{
	HBITMAP hbmpScreen = CreateCompatibleBitmap(this->hdcScreen, this->width, this->height);
	SelectObject(hdcCom, hbmpScreen);
	BitBlt(hdcCom, 0, 0, this->width, this->height, this->hdcScreen, this->x, this->y, SRCCOPY);
	
	if(ScreenData)
		free(ScreenData);
	
	ScreenData = (byte*)malloc(4 * this->width * this->height);
	
	if(ScreenData == NULL)
		return false;
	
    GetDIBits(this->hdcCom, hbmpScreen, 0, this->height, ScreenData, (BITMAPINFO*)&this->bih, DIB_RGB_COLORS);
	DeleteObject(hbmpScreen);
	
	return true;
}

int ScreenGrabber::GetIndex(int x, int y)
{
	return (y * this->width + x) * 4;
}

void ScreenGrabber::GetColor(int x, int y, byte* color)
{
	int index = GetIndex(x, y);
	
	for(int i = 0; i < 3; i++)
		color[i] = ScreenData[index + (2 - i)];		// 2-i because it needs an invert in position
}

//
//	ScreenInputter
//

ScreenInputter::ScreenInputter(ClickMode mode)
{
	this->screenWidth  		= GetSystemMetrics( SM_CXSCREEN ) - 1; 
	this->screenHeight  	= GetSystemMetrics( SM_CYSCREEN ) - 1; 
	this->screenWidthRatio 	= 65535.0f / screenWidth;
	this->screenHeightRatio	= 65535.0f / screenHeight;
	
	this->clickMode = mode;
}

void ScreenInputter::Move(int x, int y)
{
	double posX 		= x * this->screenWidthRatio;
	double posY 		= y * this->screenHeightRatio;
	
	INPUT  input		=	{0};
	input.type			= INPUT_MOUSE;
	input.mi.dwFlags  	= MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
	input.mi.dx 		= posX;
	input.mi.dy 		= posY;
	
	SendInput(1, &input, sizeof(INPUT));
}

void ScreenInputter::Click(ClickType type)
{
	INPUT input			= {0};
	input.type      	= INPUT_MOUSE;
	
	switch(type)
	{
		case ClickType::Left:
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			break;
		case ClickType::Right:
			input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			break;
		case ClickType::Middle:
			input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
			break;
	}
	
	SendInput(1, &input, sizeof(INPUT));
	ZeroMemory(&input, sizeof(INPUT));
	
	switch(type)
	{
		case ClickType::Left:
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			break;
		case ClickType::Right:
			input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			break;
		case ClickType::Middle:
			input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
			break;
	}
			
	SendInput(1, &input, sizeof(INPUT));
}

void ScreenInputter::Click(ClickType type, int x, int y)
{
	POINT p;
	if(this->clickMode == ClickMode::Revert)
		GetCursorPos(&p);
	
	Move(x, y);
	Click(type);
	
	if(this->clickMode == ClickMode::Revert)
		Move(p.x, p.y);
}

void ScreenInputter::SetClickMode(ClickMode mode)
{
	this->clickMode = mode;
}

void ScreenInputter::Delay(int milliseconds)
{
	Sleep(milliseconds);
}
