#pragma once
#include "InputHandler.h"
#include "OutputHandler.h"
#include "Television.h"
#include "LEDWall.h"

class ScreenFactory
{
public:
	typedef std::pair<std::string, std::string> RawDimensions;

	static Television* CreateTelevision(InputHandler& input, OutputHandler& output);
	static LEDWall*    CreateLedWall(InputHandler& input, OutputHandler& output);
private:
	static RawDimensions ExtractRawDimensions(InputHandler& input);
	static const char* FORMAT_STR;
};

