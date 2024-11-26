#include "IOManager.h"

IOManager::IOManager()
{
    m_input  = new InputHandler();
    m_output = new OutputHandler();

    if (!m_input)
        throw std::runtime_error("Failed to initialize input handler!");

    if (!m_output)
        throw std::runtime_error("Failed to initialize output handler!");
}

IOManager::IOManager(const InputHandler& input, const OutputHandler& output)
    : m_input(new InputHandler(input)), m_output(new OutputHandler(output))
{
    if (!m_input)
        throw std::runtime_error("Failed to initialize input handler!");

    if (!m_output)
        throw std::runtime_error("Failed to initialize output handler!");
}

InputHandler& IOManager::GetInput()
{
    return *m_input;
}

OutputHandler& IOManager::GetOutput()
{
    return *m_output;
}

IOManager::~IOManager()
{
    if(m_input != nullptr)
        delete m_input;

    if(m_output != nullptr)
        delete m_output;

    m_input  = nullptr;
    m_output = nullptr;
}
