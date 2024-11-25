#pragma once
#include "GenerationStrategy.h"

class AspectStrategy : public GenerationStrategy
{
public:
	Dimension GenerateWallDimension(const Dimension& panelSize,
		                   const Dimension& aspectRatio) const override;
};

