#pragma once
#include "Screen.h"

class Television : public Screen
{
public:
	Television();
	Television(const Dimension& other);

	virtual std::string ToString() const override;
};

