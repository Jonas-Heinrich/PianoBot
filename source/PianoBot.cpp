#include "PianoBot.h"

using namespace std;

//
//	PianoBot
//

PianoBot::PianoBot()
{
	int windowSplitH = WindowWidth / NUMBEROFTRACKS;
	int windowSplitV = WindowHeight * 2/3;
	
	this->trackLocations = new int[NUMBEROFTRACKS * 2];
	for(int i = 0; i < NUMBEROFTRACKS * 2; i += 2)
	{
		this->trackLocations[i] = WindowCordX + (i / 2) * windowSplitH + windowSplitH / 2;
		this->trackLocations[i + 1] = WindowCordY + windowSplitV;
	};
	
	this->colorTrigger = new byte[3] {5, 5, 5};
}

PianoBot::~PianoBot()
{
	free(this->trackLocations);
	free(this->colorTrigger);
}

void PianoBot::PrintStart()
{
	cout << "The game this bot can play is " << endl << GAME << "!" << endl;
	
	
	cout << "This is the programmed upper left corner of the game." << endl;
	this->inp.Move(WindowCordX, WindowCordY);
	this->WaitForInput();
	
	
	cout << "This is the programmed lower right corner of the game." << endl;
	this->inp.Move(WindowCordX + WindowWidth, WindowCordY + WindowHeight);
	this->WaitForInput();
	
	for(int i = 0; i < NUMBEROFTRACKS * 2; i += 2)
	{
		cout << "This is the track number " << (i / 2) + 1 << "." << endl;
		this->inp.Move(this->trackLocations[i], this->trackLocations[i + 1]);
		this->WaitForInput();
	}
}

void PianoBot::Start()
{
	cout << "Starting Game.." << endl;
	this->inp.SetClickMode(ClickMode::Stay);
	
	byte* color = new byte[3];
	
	int lastTrack = -1;
	
	while(1)
	{
		grb.UpdateScreen();
		
		for(int i = 0; i < NUMBEROFTRACKS * 2; i += 2)
		{
			this->grb.GetColor(trackLocations[i] - WindowCordX, trackLocations[i + 1] - WindowCordY, color);
			if(	color[0] <= colorTrigger[0] &&
				color[1] <= colorTrigger[1] &&
				color[2] <= colorTrigger[2] &&
				lastTrack != i/2)
			{
				this->inp.Click(ClickType::Left, trackLocations[i], trackLocations[i + 1]);
			}
		}
		this->grb.GetColor(EndPixelX, EndPixelY, color);
		
		if(color[0] == (byte)EndPixelR && color[1] == (byte)EndPixelG && color[2] == (byte)EndPixelB)
		{
			this->grb.GetColor(EndPixelX_Safe, EndPixelY_Safe, color);
			if(color[0] == (byte)EndPixelR_Safe && color[1] == (byte)EndPixelG_Safe && color[2] == (byte)EndPixelB_Safe)
			{
				break;
			}
		}
	}
	
	cout << "Done" << endl;
}

void PianoBot::WaitForInput()
{
	cout << "Press a key.." << endl;
	cin.ignore();
}

//
//	Main
//

int main()
{
	PianoBot bot = PianoBot();
	bot.Start();
	return 0;
}