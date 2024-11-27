#pragma once
#include "GenerationStrategy.h"

class FreeformStrategy : public GenerationStrategy
{
public:
	FreeformStrategy() = default;
	Dimension GenerateWallDimension(const Dimension& panelSize,
		                            const Dimension& maxSize) const override;

	virtual GenerationStrategy* Clone() const override;

	virtual ~FreeformStrategy() = default;
};

