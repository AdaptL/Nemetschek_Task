#include "IOManager.h"

IOManager::IOManager()
{
    m_input  = new InputHandler();
    m_output = new OutputHandler();
}

IOManager::IOManager(const InputHandler& input, const OutputHandler& output)
    : m_input(new InputHandler(input)), m_output(new OutputHandler(output))
{}

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
    delete m_input;
    delete m_output;
}
