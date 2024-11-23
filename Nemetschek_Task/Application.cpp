#include <string>
#include <iostream>
#include "Application.h"

Application::Application() : m_console(new IOManager())
{}

void Application::Run()
{
    std::string input;

    m_console->GetOutput().Initial();

    while (true)
    {
        m_console->GetOutput().CustomMsg(">", false);

        input     = m_console->GetInput().GetUserInput();

        if (!ExecuteLogic(input))
            break;
    }
}

bool Application::ExecuteLogic(const std::string& input)
{
    using InputType = InputHandler::INPUT_TYPE;

    InputType inputType;
    inputType = m_console->GetInput().GetUserInputType(input);

    if (inputType == InputType::INVALID)
        m_console->GetOutput().ErrMsg("Please enter valid input! Type (help) for options.");

    switch (inputType)
    {
    case InputType::CREATE:
        break;
    case InputType::PRINT:
        break;
    case InputType::HELP:
        m_console->GetOutput().Options();
        break;
    case InputType::EXIT:
        return false;
        break;
    default:
        break;
    }

    return true;
}

Application::~Application()
{
    delete m_console;
}