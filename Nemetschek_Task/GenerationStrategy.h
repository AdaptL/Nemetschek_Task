#pragma once
#include "Dimension.h"

class GenerationStrategy
{
public:
    virtual Dimension GenerateWall(const Dimension& panelSize, const Dimension& maxSizeOrRatio) const = 0;
    virtual ~GenerationStrategy() = default;
};
