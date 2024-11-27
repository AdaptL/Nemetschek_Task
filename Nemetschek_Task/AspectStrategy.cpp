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

    unsigned numerator = unitWidth;
    unsigned denominator = unitHeight;

    unsigned numenatorMultiple = numerator * panelSize.GetHeight();
    unsigned denominatorMultiple = denominator * panelSize.GetWidth();

    unsigned gcd = Dimension::AspectRatio::CalculateAspectGCD(numenatorMultiple,
                                                              denominatorMultiple);

    double columns = numenatorMultiple / gcd;
    double rows = denominatorMultiple / gcd;

    unsigned wallWidth  = round(columns) * panelSize.GetWidth();
    unsigned wallHeight = round(rows) * panelSize.GetHeight();

    result = Dimension(wallWidth, wallHeight);

    result.SetAspectRatio(Dimension::AspectRatio(columns, rows));

    return result;
}

GenerationStrategy* AspectStrategy::Clone() const
{
    return new AspectStrategy(*this);
}
