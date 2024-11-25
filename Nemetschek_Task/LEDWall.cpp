#include <stdexcept>
#include "LEDWall.h"

LEDWall::LEDWall(const Dimension& panelSize, GenerationStrategy* strategy)
	:m_panelSize(new Dimension(panelSize)), m_strategy(strategy)
{
	if (!m_panelSize)
		throw std::runtime_error("Failed to initialize panel size for LEDWall!");

	if(!m_strategy)
		throw std::runtime_error("Failed to initialize strategy for LEDWall!");
}

void LEDWall::SetStrategy(GenerationStrategy* strategy)
{
	if (m_strategy)
		delete m_strategy;

	m_strategy = strategy;

	if (!m_strategy)
		throw std::invalid_argument("Cannot set strategy to null!");
}

void LEDWall::SetDimensions(const Dimension& maxSizeOrRatio)
{
	if (!m_panelSize)
		throw std::runtime_error("Panel size cannot be null when setting dimensions!");

	Screen::SetDimensions(m_strategy->GenerateWallDimension(*m_panelSize, maxSizeOrRatio));
}

std::string LEDWall::ToString() const
{
	return "LedWall: " + Screen::ToString() + "Panel " + m_panelSize->ToString();
}

LEDWall::~LEDWall()
{
	if (m_strategy != nullptr)
		delete m_strategy;

	m_strategy = nullptr;
}