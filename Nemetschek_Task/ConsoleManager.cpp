#include "ConsoleManager.h"
#include <iostream>
#include <map>

const std::map<std::string, std::string> ConsoleManager::m_optionsToDesc =
{
    {"create <screen_type>", "create a new screen object. Screen types - TV, LED wall."},
    {"print", "prints all created screen objects"},
    {"help", "display available options."},
    {"exit", "close the application."}
};

ConsoleManager::ConsoleManager()
{
    this->initialMsg = "Welcome! Type help to see command options!";
}

ConsoleManager::ConsoleManager(std::string initialMsg) : initialMsg(initialMsg)
{}

void ConsoleManager::Initial() const
{
    std::cout << this->initialMsg << std::endl;
}

void ConsoleManager::Options() const
{
    for (const auto& opt : this->m_optionsToDesc)
    {
        std::cout << "Enter: " << opt.first << " - To " << opt.second << std::endl;
    }
}

void ConsoleManager::CustomMsg(const std::string& msg) const
{
    std::cout << msg << std::endl;
}

void ConsoleManager::ErrMsg(const std::string& msg) const
{
    std::cerr << msg << std::endl;
}

std::string ConsoleManager::GetUserInput() const
{
    std::string input;
    do
    {
        std::cout << "> ";
        std::getline(std::cin, input);
    } while (input.empty());

    return input;
}
