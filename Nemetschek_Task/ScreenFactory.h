#pragma once
#include "InputHandler.h"
#include "OutputHandler.h"
#include "Television.h"
#include "LEDWall.h"

class ScreenFactory
{
public:
	static Television* CreateTelevision(InputHandler& input, OutputHandler& output);
	static LEDWall*    CreateLed(InputHandler& input, OutputHandler& output);
};
