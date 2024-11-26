#pragma once
#include "InputHandler.h"
#include "OutputHandler.h"
#include "Television.h"
#include "LEDWall.h"

class ScreenFactory
{
public:
	struct RawDimensions
	{
		RawDimensions(std::string first, std::string second, bool isAspect)
			: first(first), second(second), isAspect(isAspect) {}

		std::string first;
		std::string second;
		bool isAspect;
	};

	static Television* CreateTelevision(InputHandler& input, OutputHandler& output);
	static LEDWall*    CreateLedWall(InputHandler& input, OutputHandler& output);
private:
	static RawDimensions ExtractRawDimensions(InputHandler& input);

	static Dimension     GetValidDimensions(InputHandler& input, OutputHandler& output,
		                                    const std::string& prompt);

	static const char* FORMAT_STR;
};

