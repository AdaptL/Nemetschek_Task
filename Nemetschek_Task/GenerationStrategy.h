#pragma once
#include "Dimension.h"

class GenerationStrategy
{
public:
    GenerationStrategy() = default;

    virtual Dimension GenerateWallDimension(const Dimension& panelSize,
                                            const Dimension& maxSizeOrRatio) const = 0;

    virtual GenerationStrategy* Clone() const = 0;

    virtual ~GenerationStrategy() = default;
};
