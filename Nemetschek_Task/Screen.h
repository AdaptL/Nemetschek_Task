#pragma once
#include "Dimension.h"

class Screen : public IDataObject
{
public:
	Screen();
	Screen(const Dimension& other);

	Screen(const Screen& other);
	Screen(Screen&& other) noexcept;

	Screen& operator=(const Screen& other);
	Screen& operator=(Screen&& other) noexcept;

	Dimension GetDimensions() const;

	virtual void SetDimensions(const Dimension& other);

	virtual ~Screen();
private:
	void InitDefaultDimension();

	Dimension* m_dimensions;
};

