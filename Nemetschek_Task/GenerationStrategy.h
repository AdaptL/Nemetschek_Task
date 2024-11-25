#pragma once
#include "Dimension.h"

class GenerationStrategy
{
public:
    virtual Dimension GenerateWallDimension(const Dimension& panelSize,
                                            const Dimension& maxSizeOrRatio) const = 0;
    virtual ~GenerationStrategy() = default;
};
