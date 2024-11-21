#include "Application.h"
#include <string>
#include <iostream>

Application::Application()
{
}

void Application::Run()
{
    std::string input;

    while (true)
    {
        std::cout << "> ";

        std::getline(std::cin, input);

        if (input.find("exit") != std::string::npos)
        {
            break;
        }
    }
}

Application::~Application()
{
}
