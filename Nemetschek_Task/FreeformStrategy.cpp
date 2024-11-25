#include "FreeformStrategy.h"

Dimension FreeformStrategy::GenerateWallDimension(const Dimension& panelSize, 
                                         const Dimension& maxSize) const
{
    unsigned cols = maxSize.GetWidth() / panelSize.GetWidth();
    unsigned rows = maxSize.GetHeight() / panelSize.GetHeight();

    unsigned wallWidth = cols * panelSize.GetWidth();
    unsigned wallHeight = rows * panelSize.GetHeight();

    return Dimension(wallWidth, wallHeight);
}
