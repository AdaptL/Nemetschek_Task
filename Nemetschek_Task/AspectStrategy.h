#pragma once
#include "GenerationStrategy.h"

class AspectStrategy : public GenerationStrategy
{
public:
	Dimension GenerateWall(const Dimension& panelSize,
		                   const Dimension& aspectRatio) const override;
};

