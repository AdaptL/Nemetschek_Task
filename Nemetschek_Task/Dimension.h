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
		AspectRatio(unsigned w, unsigned h) : width(w), height(h) {}
		unsigned width;
		unsigned height;
	};
	Dimension();
	Dimension(unsigned width, unsigned height);
	Dimension(unsigned width, unsigned height, Units unitType);
	Dimension(const AspectRatio& ratio);

	Dimension(const Dimension& other);
	Dimension(Dimension&& other) noexcept;

	Dimension& operator=(const Dimension& other);
	Dimension& operator=(Dimension&& other) noexcept;

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

	~Dimension();
private:
	unsigned ConvertToMillimetres(unsigned value, Units unit) const;
	unsigned ConvertToUnit(unsigned value, Units unit)        const;

	unsigned GCD(unsigned a, unsigned b) const;

	unsigned   m_width;
	unsigned   m_height;
	Units      m_currentUnit;

	AspectRatio* m_ratio;
};

