#pragma once
#include "ConsoleManager.h"
class Application
{
public:
	Application();

	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	bool operator==(const Application& other) = delete;

	void Run();

	~Application();
private:
	ConsoleManager* m_consoleManager;

	bool HandleInput(const std::string& input);
};

