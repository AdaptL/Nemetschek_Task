#include <iostream>
#include "OutputHandler.h"

OutputHandler::OutputHandler() : OutputHandler(DEFAULT_INITIAL_MSG)
{}

OutputHandler::OutputHandler(std::string initialMsg) : m_initialMsg(initialMsg)
{
    m_inputsDesc = new DescriptionMap
    {
        {InputType::CREATE, "create - creates a new screen object. Screen types - TV, LED wall."},
        {InputType::PRINT,  "print - prints all created screen objects"},
        {InputType::HELP,   "help - display available options."},
        {InputType::EXIT,   "exit - close the application."}
    };
}

OutputHandler::OutputHandler(const OutputHandler& other)
    : m_initialMsg(other.m_initialMsg)
{
    this->m_inputsDesc = new DescriptionMap(*other.m_inputsDesc);
}

OutputHandler::OutputHandler(OutputHandler&& other) noexcept
    : m_initialMsg(std::move(other.m_initialMsg)), m_inputsDesc(other.m_inputsDesc)
{
    other.m_inputsDesc = nullptr;
}

OutputHandler& OutputHandler::operator=(const OutputHandler& other)
{
    if (this != &other)
    {
        this->m_initialMsg = other.m_initialMsg;

        delete this->m_inputsDesc;
        this->m_inputsDesc = new DescriptionMap(*other.m_inputsDesc);
    }
    return *this;
}

OutputHandler& OutputHandler::operator=(OutputHandler&& other) noexcept
{
    if (this != &other) 
    {
        delete m_inputsDesc;

        m_initialMsg = std::move(other.m_initialMsg);
        m_inputsDesc = other.m_inputsDesc;

        other.m_inputsDesc = nullptr;
    }
    return *this;
}

std::string OutputHandler::GetDesc(InputType type) const
{
    auto result = m_inputsDesc->find(type);

    if(result != m_inputsDesc->end())
        return result->second;

    return "";
}

std::string OutputHandler::GetInitial() const
{
    return m_initialMsg;
}

void OutputHandler::SetInitial(const std::string& msg)
{
    this->m_initialMsg = msg;
}

bool OutputHandler::SetDescription(InputType type, const std::string& desc)
{
    auto result = m_inputsDesc->find(type);

    if (result != m_inputsDesc->end())
    {
        result->second = desc;
        return true;
    }

    return false;
}

void OutputHandler::Initial() const
{
    std::cout << m_initialMsg << std::endl;
}

void OutputHandler::Options() const
{
    for (const auto& option : *m_inputsDesc)
    {
        std::cout << option.second << std::endl;
    };
    std::cout << std::endl;
}

void OutputHandler::CustomMsg(const std::string& msg, bool endl) const
{
    if (endl)
        std::cout << msg << std::endl;
    else
        std::cout << msg;
}

void OutputHandler::ErrMsg(const std::string& msg) const
{
    std::cerr << msg << std::endl;
}

OutputHandler::~OutputHandler()
{
    delete m_inputsDesc;
}
