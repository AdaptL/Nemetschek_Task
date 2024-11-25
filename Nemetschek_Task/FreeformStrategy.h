#pragma once
#include "GenerationStrategy.h"

class FreeformStrategy : public GenerationStrategy
{
public:
	Dimension GenerateWall(const Dimension& panelSize,
		                   const Dimension& maxSize) const override;
};

