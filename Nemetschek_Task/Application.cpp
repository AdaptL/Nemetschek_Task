#include <string>
#include <iostream>
#include "Application.h"
#include "ScreenFactory.h"

Application::Application() : m_console(new IOManager())
{
    if(!m_console)
        throw std::runtime_error("Failed to initialize IOManager!");
}

void Application::Run()
{
    std::string userInput;

    InputHandler&  inputHandler  = m_console->GetInput();
    OutputHandler& outputHandler = m_console->GetOutput();

    outputHandler.Initial();

    while (true)
    {
        outputHandler.CustomMsg(">", false);

        userInput = inputHandler.GetUserInput();

        if (!ExecuteLogic(userInput))
            break;
    }
}

bool Application::ExecuteLogic(const std::string& input)
{
    using InputType = InputHandler::INPUT_TYPE;

    InputHandler&  inputHandler  = m_console->GetInput();
    OutputHandler& outputHandler = m_console->GetOutput();

    InputType inputType;
    inputType = inputHandler.GetUserInputType(input);

    if (inputType == InputType::INVALID)
        outputHandler.ErrMsg("Please enter valid input! Type (help) for options.");

    switch (inputType)
    {
    case InputType::CREATE:
        
        if(!CreateObject())
            outputHandler.ErrMsg("Failed to create object, please try again.");

        break;
    case InputType::PRINT:

        if (m_objects.empty())
        {
            outputHandler.CustomMsg("No created screens yet!", true);
            break;
        }

        for (const auto& obj : m_objects)
            outputHandler.PrintDataObject(*obj);

        break;
    case InputType::HELP:
        outputHandler.Options();
        break;
    case InputType::EXIT:
        return false;
    default:
        break;
    }

    return true;
}

bool Application::CreateObject()
{
    InputHandler&  inputHandler  = m_console->GetInput();
    OutputHandler& outputHandler = m_console->GetOutput();

    std::string televisionStr = "television";
    std::string ledStr        = "ledwall";

    auto normalizeString = [](const std::string& str)
    {
        std::string result;
        for (char ch : str)
        {
            if (!std::isspace(ch))
            {
                result.push_back(std::tolower(ch));
            }
        }
        return result;
    };

    outputHandler.CustomMsg("Enter desired screen type! Types: <LedWall>/<Television>", true);
    std::string input = inputHandler.GetUserInput();
    
    while (input != televisionStr && input != ledStr)
    {
        outputHandler.CustomMsg("Please enter a valid screen type! Types: <LedWall>/<Television>", true);
        input = inputHandler.GetUserInput();
    }

    if (input == televisionStr)
    {
        m_objects.push_back(ScreenFactory::CreateTelevision(inputHandler,
                                                            outputHandler));
    }
    else
    {
        m_objects.push_back(ScreenFactory::CreateLedWall(inputHandler,
            outputHandler));
    }

    auto it = m_objects.end() - 1;

    if (!*it)
        return false;

    return true;
}

Application::~Application()
{
    if(m_console != nullptr)
        delete m_console;

    m_console = nullptr;
}