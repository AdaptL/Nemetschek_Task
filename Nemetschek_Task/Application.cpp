#include <string>
#include <iostream>
#include "Application.h"

Application::Application() : m_consoleManager(new ConsoleManager())
{}

void Application::Run()
{
    std::string input;

    this->m_consoleManager->Initial();

    while (true)
    {
        input = this->m_consoleManager->GetUserInput();
        
        if (!HandleInput(input))
            break;
    }
}

Application::~Application()
{
    delete m_consoleManager;
}

bool Application::HandleInput(const std::string& input)
{
    if (input == "exit")
    {
        return false;
    }
    else if (input == "help")
    {
        this->m_consoleManager->Options();
        return true;
    }
    else if (input == "print")
    {
        //for each screen, get it's string info and put it in the console manager Custom method.
        return true;
    }
    else if (input.find("create") != std::string::npos)
    {
        //handle creation of each scree, add them to the vector of screens.
        return true;
    }

    this->m_consoleManager->ErrMsg("Please enter valid input! Type (help) for options.");
    return true;
}
