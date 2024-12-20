#include <stdexcept>
#include <sstream>
#include <numeric>
#include "Dimension.h"


Dimension::Dimension()
    : m_width(0), m_height(0), m_currentUnit(Units::MILLIMETER), m_ratio(nullptr)
{}

Dimension::Dimension(unsigned width, unsigned height)
    : Dimension(width, height, Units::MILLIMETER) {}

Dimension::Dimension(unsigned width, unsigned height, Units unitType)
    : m_ratio(nullptr)
{
    SetWidth(width, unitType);
    SetHeight(height, unitType);
    this->m_currentUnit = unitType;
}

Dimension::Dimension(const AspectRatio& ratio)
    : Dimension(0,0,Units::MILLIMETER)
{
    this->m_ratio = new AspectRatio(ratio);
    if (!this->m_ratio)
        throw std::runtime_error("Failed to initialize aspect ratio!");
}

Dimension::Dimension(const Dimension& other)
    :
    m_width(other.m_width),
    m_height(other.m_height),
    m_currentUnit(other.m_currentUnit),
    m_ratio(other.m_ratio ? new AspectRatio(*other.m_ratio) : nullptr)
{}

Dimension& Dimension::operator=(const Dimension& other)
{
    if (this == &other)
        return *this; 

    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_currentUnit = other.m_currentUnit;

    if(this->m_ratio != nullptr)
        delete this->m_ratio;

    this->m_ratio = other.m_ratio ? new AspectRatio(*other.m_ratio) : nullptr;

    return *this;
}

Dimension::Dimension(Dimension&& other) noexcept
    : m_width(other.m_width),
    m_height(other.m_height),
    m_currentUnit(other.m_currentUnit),
    m_ratio(other.m_ratio)
{
    other.m_width  = 0;
    other.m_height = 0;
    other.m_currentUnit = Units::MILLIMETER;
    other.m_ratio  = nullptr;
}

Dimension& Dimension::operator=(Dimension&& other) noexcept
{
    if (this == &other)
        return *this; 

    if(this->m_ratio != nullptr)
        delete this->m_ratio;

    m_width  = other.m_width;
    m_height = other.m_height;
    m_currentUnit = other.m_currentUnit;
    m_ratio  = other.m_ratio;

    other.m_width  = 0;
    other.m_height = 0;
    other.m_currentUnit = Units::MILLIMETER;
    other.m_ratio  = nullptr;

    return *this;
}

unsigned Dimension::ConvertUnitValue(unsigned value, Units from, Units to)
{
    unsigned result = 0;

    if (from != Units::MILLIMETER)
        result = ConvertToMillimetres(value, from);
    else
        result = value;

    if (to == Units::MILLIMETER)
        return result;

    result = ConvertToUnit(result, to);

    return result;
}

bool Dimension::isAspect() const
{
    if (m_ratio != nullptr)
        return true;

    return false;
}

unsigned Dimension::GetWidth() const
{
    if (m_ratio != nullptr)
        return m_ratio->columns;

    return ConvertToUnit(m_width, m_currentUnit);
}

unsigned Dimension::GetHeight() const
{
    if (m_ratio != nullptr)
        return m_ratio->rows;

    return ConvertToUnit(m_height, m_currentUnit);
}

unsigned Dimension::GetWidth(Units unit) const
{
    return ConvertToUnit(m_width, unit);
}

unsigned Dimension::GetHeight(Units unit) const
{
    return ConvertToUnit(m_height, unit);
}

Dimension::Units Dimension::GetUnits() const
{
    return m_currentUnit;
}

unsigned Dimension::ConvertWidthToAspectRatio() const
{
    unsigned gcd = Dimension::GCD(m_width, m_height);
    return m_width / gcd;
}

unsigned Dimension::ConvertHeightToAspectRatio() const
{
    unsigned gcd = Dimension::GCD(m_width, m_height);
    return m_height / gcd;
}

void Dimension::SetWidth(unsigned width, Units unit)
{
    if (m_ratio != nullptr) 
    {
        m_ratio->columns = width;
        return;
    }
    
    m_width = ConvertToMillimetres(width, unit);
}

void Dimension::SetHeight(unsigned height, Units unit)
{
    if (m_ratio != nullptr)
    {
        m_ratio->rows = height;
        return;
    }
    m_height = ConvertToMillimetres(height, unit);
}

void Dimension::SetUnits(Units unit)
{
    m_currentUnit = unit;
}

void Dimension::SetAspectRatio(const AspectRatio& ratio)
{
    if (this->m_ratio == nullptr)
    {
        this->m_ratio = new AspectRatio(ratio);
        if (!this->m_ratio)
            throw std::runtime_error("Failed to initialize aspect ratio!");
        return;
    }

    this->m_ratio->columns = ratio.columns;
    this->m_ratio->rows    = ratio.rows;
}

std::string Dimension::ToString() const
{
    std::ostringstream result;
    std::string unitStr = "";

    switch (m_currentUnit)
    {
    case Units::MILLIMETER:
        unitStr = MILLIMETER_STR;
        break;
    case Units::CENTIMETER:
        unitStr = CENTIMETER_STR;
        break;
    case Units::METER:
        unitStr = METER_STR;
        break;
    default:
        throw std::runtime_error("Unknown unit type");
    }

    std::string seperationStr = (m_ratio == nullptr ? " x " : ":");

    result << "Dimensions: "
        << GetWidth(m_currentUnit)  << unitStr << seperationStr
        << GetHeight(m_currentUnit) << unitStr;

    return result.str();
}

unsigned Dimension::ConvertToUnit(unsigned value, Units unit)
{
    switch (unit)
    {
    case Units::MILLIMETER:
        return value;
    case Units::CENTIMETER:
        return value / 10;
    case Units::METER:
        return value / 1000;
    default:
        throw std::runtime_error("Unknown unit type");
    }
}

unsigned Dimension::ConvertToMillimetres(unsigned value, Units unit)
{
    switch (unit)
    {
    case Units::MILLIMETER:
        return value;
    case Units::CENTIMETER:
        return value * 10;
    case Units::METER:
        return value * 1000;
    default:
        throw std::runtime_error("Unknown unit type");
    }
}

unsigned Dimension::GCD(unsigned a, unsigned b)
{
    while (b != 0)
    {
        unsigned temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


Dimension::~Dimension()
{
    if (m_ratio != nullptr)
        delete m_ratio;

    m_ratio = nullptr;
}

unsigned Dimension::AspectRatio::CalculateAspectGCD(unsigned a, unsigned b)
{
    return Dimension::GCD(a,b);
}
