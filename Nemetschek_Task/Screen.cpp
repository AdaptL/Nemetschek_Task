#include <stdexcept>
#include "Screen.h"

Screen::Screen()
{
	InitDefaultDimension();
}

Screen::Screen(const Dimension& other)
	: m_dimensions(new Dimension(other))
{
	if (!m_dimensions)
		throw std::runtime_error("Failed to initialize dimension for screen!");
}

Screen::Screen(const Screen& other)
	: m_dimensions(other.m_dimensions ? new Dimension(*other.m_dimensions) : nullptr)
{
	if (!m_dimensions)
	{
		InitDefaultDimension();
	}
}

Screen& Screen::operator=(const Screen& other)
{
	if (this == &other)
		return *this; 

	delete m_dimensions;

	m_dimensions = other.m_dimensions ? new Dimension(*other.m_dimensions) : nullptr;

	if (!m_dimensions)
	{
		InitDefaultDimension();
	}

	return *this;
}

Screen::Screen(Screen&& other) noexcept
	: m_dimensions(other.m_dimensions)
{
	other.m_dimensions = nullptr; 

	if (!m_dimensions)
		InitDefaultDimension();
}

Screen& Screen::operator=(Screen&& other) noexcept
{
	if (this == &other)
		return *this;  

	delete m_dimensions;

	m_dimensions = other.m_dimensions;
	other.m_dimensions = nullptr;

	if (!m_dimensions)
		InitDefaultDimension();

	return *this;
}

Dimension Screen::GetDimensions() const
{
	return *m_dimensions;
}

void Screen::SetDimensions(const Dimension& other)
{
	if (m_dimensions != nullptr)
	{
		m_dimensions->SetUnits(other.GetUnits());

		m_dimensions->SetWidth(other.GetWidth());
		m_dimensions->SetHeight(other.GetHeight());

		if (other.isAspect())
			m_dimensions->SetAspectRatio(Dimension::AspectRatio(other.GetWidth(), other.GetHeight()));

		return;
	}

	m_dimensions = new Dimension(other);

	if (!m_dimensions)
		throw std::runtime_error("Failed to set dimensions of screen!");
}

std::string Screen::ToString() const
{
	return m_dimensions->ToString();
}

Screen::~Screen()
{
	if (m_dimensions != nullptr)
		delete m_dimensions;

	m_dimensions = nullptr;
}

void Screen::InitDefaultDimension()
{
	if (m_dimensions)
		return;

	m_dimensions = new Dimension(0, 0);
	if (!m_dimensions)
		throw std::runtime_error("Failed to initialize screen default dimensions!");
}
