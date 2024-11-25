#include <stdexcept>
#include "AspectStrategy.h"

Dimension AspectStrategy::GenerateWallDimension(const Dimension& panelSize,
                                                const Dimension& aspectRatio) const
{
    unsigned unitWidth;
    unsigned unitHeight;

    if (!aspectRatio.isAspect())
    {
        unitWidth  = aspectRatio.ConvertWidthToAspectRatio();
        unitHeight = aspectRatio.ConvertHeightToAspectRatio();
    }
        
    unitWidth  = aspectRatio.GetWidth();
    unitHeight = aspectRatio.GetHeight();

    unsigned cols = panelSize.GetWidth()  * unitWidth;
    unsigned rows = panelSize.GetHeight() * unitHeight;

    unsigned wallWidth  = cols;
    unsigned wallHeight = rows;

    return Dimension(wallWidth, wallHeight);
}
