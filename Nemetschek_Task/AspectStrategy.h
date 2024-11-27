#pragma once
#include "GenerationStrategy.h"

class AspectStrategy : public GenerationStrategy
{
public:
	AspectStrategy() = default;

	Dimension GenerateWallDimension(const Dimension& panelSize,
		                            const Dimension& aspectRatio) const override;

	virtual GenerationStrategy* Clone() const override;

	virtual ~AspectStrategy() = default;
};

