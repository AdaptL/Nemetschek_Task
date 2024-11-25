#pragma once
#include "Screen.h"

class Television : public Screen
{
public:
	virtual std::string ToString() const override;
};

