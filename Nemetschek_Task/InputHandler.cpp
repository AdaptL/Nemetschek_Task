#include <iostream>
#include "InputHandler.h"

const std::unordered_map<std::string, InputHandler::INPUT_TYPE> InputHandler::m_typeToStr =
{
    {"create", INPUT_TYPE::CREATE},
    {"print",  INPUT_TYPE::PRINT},
    {"help",   INPUT_TYPE::HELP},
    {"exit",   INPUT_TYPE::EXIT}
};

std::string InputHandler::GetUserInput() const
{
    std::string input;
    do
    {
        std::getline(std::cin, input);
    } while (input.empty());

    return input;
}

InputHandler::INPUT_TYPE InputHandler::GetUserInputType(const std::string& input) const
{
    auto result = m_typeToStr.find(input);
    if (result != m_typeToStr.end())
        return result->second;

    return INPUT_TYPE::INVALID;
}
