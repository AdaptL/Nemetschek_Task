#pragma once
#include "IDataObject.h"

#define MILLIMETER_STR "mm"
#define CENTIMETER_STR "cm"
#define METER_STR      "m"

class Dimension : public IDataObject
{
public:
	enum class Units { MILLIMETER, CENTIMETER, METER };

	struct AspectRatio
	{
		AspectRatio(unsigned cols, unsigned rows) : columns(cols), rows(rows) {}

		static unsigned CalculateAspectGCD(unsigned a, unsigned b);

		unsigned columns;
		unsigned rows;   
	};
	Dimension();
	Dimension(unsigned width, unsigned height);
	Dimension(unsigned width, unsigned height, Units unitType);
	Dimension(const AspectRatio& ratio);

	Dimension(const Dimension& other);
	Dimension(Dimension&& other) noexcept;

	Dimension& operator=(const Dimension& other);
	Dimension& operator=(Dimension&& other) noexcept;

	static unsigned ConvertUnitValue(unsigned value, Units from, Units to);

	bool isAspect() const;

	unsigned ConvertWidthToAspectRatio()  const;
	unsigned ConvertHeightToAspectRatio() const;

	unsigned GetWidth()            const;
	unsigned GetHeight()           const;
	unsigned GetWidth(Units unit)  const;
	unsigned GetHeight(Units unit) const;
	Units    GetUnits()            const;

	void SetWidth(unsigned width,   Units unit = Units::MILLIMETER);
	void SetHeight(unsigned height, Units unit = Units::MILLIMETER);
	void SetUnits(Units unit);
	void SetAspectRatio(const AspectRatio& ratio);

	std::string ToString() const override;

	virtual ~Dimension();
private:
	static unsigned ConvertToMillimetres(unsigned value, Units unit);
	static unsigned ConvertToUnit(unsigned value, Units unit);

	static unsigned GCD(unsigned a, unsigned b);

	unsigned   m_width;
	unsigned   m_height;
	Units      m_currentUnit;

	AspectRatio* m_ratio;
};

