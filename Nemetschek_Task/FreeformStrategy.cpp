#include "FreeformStrategy.h"

Dimension FreeformStrategy::GenerateWallDimension(const Dimension& panelSize, 
                                                  const Dimension& maxSize) const
{
    Dimension result;

    unsigned cols = maxSize.GetWidth() / panelSize.GetWidth();
    unsigned rows = maxSize.GetHeight() / panelSize.GetHeight();

    unsigned wallWidth  = cols * panelSize.GetWidth();
    unsigned wallHeight = rows * panelSize.GetHeight();

    result = Dimension(wallWidth, wallHeight);
    result.SetAspectRatio(Dimension::AspectRatio(cols,rows));

    return result;
}
