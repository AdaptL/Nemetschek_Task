#pragma once
#include <vector>
#include "IOManager.h"
#include "Screen.h"

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
	bool ExecuteLogic(const std::string& input);
	bool CreateObject();

	std::vector<Screen*> m_objects;
	IOManager*           m_console;
};

