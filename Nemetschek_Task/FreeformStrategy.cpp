#include <stdexcept>
#include "FreeformStrategy.h"

Dimension FreeformStrategy::GenerateWallDimension(const Dimension& panelSize, 
                                                  const Dimension& maxSize) const
{
    Dimension result;

    if (panelSize.GetWidth() == 0 || panelSize.GetHeight() == 0)
        throw std::invalid_argument("Panel width or height cannot be zero!");

    unsigned cols = maxSize.GetWidth() / panelSize.GetWidth();
    unsigned rows = maxSize.GetHeight() / panelSize.GetHeight();

    unsigned wallWidth  = cols * panelSize.GetWidth();
    unsigned wallHeight = rows * panelSize.GetHeight();

    result = Dimension(wallWidth, wallHeight);
    result.SetAspectRatio(Dimension::AspectRatio(cols,rows));

    return result;
}

GenerationStrategy* FreeformStrategy::Clone() const
{
    return new FreeformStrategy(*this);
}
