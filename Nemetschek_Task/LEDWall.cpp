#include <stdexcept>
#include "LEDWall.h"

LEDWall::LEDWall(const Dimension& panelSize, const Dimension& maxSizeOrRatio, GenerationStrategy* strategy)
	: Screen(), m_panelSize(new Dimension(panelSize)), rows(0), columns(0)
{
	this->SetStrategy(strategy);

	if (!this->m_strategy)
		throw std::runtime_error("Failed to initialize strategy for LEDWall!");

	if (!this->m_panelSize)
		throw std::runtime_error("Failed to initialize panel size for LEDWall!");

	this->SetDimensions(maxSizeOrRatio);
}

LEDWall::LEDWall(const LEDWall& other)
    : Screen(other),
    m_panelSize(other.m_panelSize ? new Dimension(*other.m_panelSize) : nullptr),
    rows(other.rows),
    columns(other.columns),
    m_strategy(other.m_strategy ? other.m_strategy->Clone() : nullptr)
{}

LEDWall::LEDWall(LEDWall&& other) noexcept
    : Screen(std::move(other)),
    m_panelSize(other.m_panelSize),
    rows(other.rows),
    columns(other.columns),
    m_strategy(other.m_strategy)
{
    other.m_panelSize = nullptr;
    other.m_strategy = nullptr;
}

LEDWall& LEDWall::operator=(const LEDWall& other)
{
    if (this != &other)
    {
        Screen::operator=(other);
        
        if(m_panelSize != nullptr)
            delete m_panelSize;
        
        if(m_strategy != nullptr)
            delete m_strategy;

        m_panelSize = other.m_panelSize ? new Dimension(*other.m_panelSize) : nullptr;
        m_strategy = other.m_strategy ? other.m_strategy->Clone() : nullptr;

        rows = other.rows;
        columns = other.columns;
    }
    return *this;
}

LEDWall& LEDWall::operator=(LEDWall&& other) noexcept
{
    if (this != &other)
    {
        Screen::operator=(std::move(other));
        
        if(m_panelSize != nullptr)
            delete m_panelSize;
        if(m_strategy != nullptr)
            delete m_strategy;

        m_panelSize = other.m_panelSize;
        m_strategy = other.m_strategy;
        rows = other.rows;
        columns = other.columns;

        other.m_panelSize = nullptr;
        other.m_strategy = nullptr;
    }
    return *this;
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

	Dimension temp = m_strategy->GenerateWallDimension(*m_panelSize, maxSizeOrRatio);
	Screen::SetDimensions(temp);
	columns = temp.GetWidth();
	rows    = temp.GetHeight();
}

std::string LEDWall::ToString() const
{
	std::string screenStr      = "LedWall: " + Screen::ToString();
	std::string panelStr       = ", Panel " + m_panelSize->ToString();
	std::string columnsRowsStr = " ( Rows:" + std::to_string(rows) +
							     " Columns:" + std::to_string(columns) + " )";

	return screenStr + columnsRowsStr + panelStr;
}

LEDWall::~LEDWall()
{
	if (m_strategy != nullptr)
		delete m_strategy;

	if (m_panelSize != nullptr)
		delete m_panelSize;

	m_strategy = nullptr;
	m_panelSize = nullptr;
}
