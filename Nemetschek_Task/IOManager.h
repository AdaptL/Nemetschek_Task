#pragma once
#include "InputHandler.h"
#include "OutputHandler.h"
class IOManager
{
public:
	IOManager();
	IOManager(const InputHandler& input, const OutputHandler& output);

	IOManager(const IOManager& other)            = delete;
	IOManager& operator=(const IOManager& other) = delete;
	bool operator==(const IOManager& other)      = delete;
	IOManager(IOManager&& other)                 = delete;
	IOManager& operator=(IOManager&& other)      = delete;

	InputHandler&  GetInput();
	OutputHandler& GetOutput();

	~IOManager();
private:
	InputHandler*  m_input;
	OutputHandler* m_output;
};

