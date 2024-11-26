#include <stdexcept>
#include "AspectStrategy.h"

Dimension AspectStrategy::GenerateWallDimension(const Dimension& panelSize,
                                                const Dimension& aspectRatio) const
{
    if (panelSize.GetWidth() == 0 || panelSize.GetHeight() == 0)
        throw std::invalid_argument("Invalid panel size: Width or height cannot be zero.");

    Dimension result;

    unsigned unitWidth;
    unsigned unitHeight;

    if (!aspectRatio.isAspect())
    {
        unitWidth  = aspectRatio.ConvertWidthToAspectRatio();
        unitHeight = aspectRatio.ConvertHeightToAspectRatio();
    }
    else
    {
        unitWidth  = aspectRatio.GetWidth();
        unitHeight = aspectRatio.GetHeight();
    }
       
    unsigned wallWidth  = panelSize.GetWidth()  * unitWidth;
    unsigned wallHeight = panelSize.GetHeight() * unitHeight;

    result = Dimension(wallWidth, wallHeight);

    result.SetAspectRatio(Dimension::AspectRatio(unitWidth, unitHeight));

    return result;
}
