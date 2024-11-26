#pragma once
#include "GenerationStrategy.h"

class FreeformStrategy : public GenerationStrategy
{
public:
	Dimension GenerateWallDimension(const Dimension& panelSize,
		                            const Dimension& maxSize) const override;

	virtual ~FreeformStrategy() = default;
};

