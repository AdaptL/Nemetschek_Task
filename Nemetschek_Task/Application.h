#pragma once
#include "IOManager.h"
class Application
{
public:
	Application();

	Application(const Application& other)            = delete;
	Application& operator=(const Application& other) = delete;
	bool operator==(const Application& other)        = delete;
	Application(Application&& other)                 = delete;
	Application& operator=(Application&& other)      = delete;

	void Run();

	~Application();
private:
	IOManager* m_console;

	bool ExecuteLogic(const std::string& input);
};

