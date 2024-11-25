#include <regex>
#include "ScreenFactory.h"
#include "AspectStrategy.h"
#include "FreeformStrategy.h"

const char* ScreenFactory::FORMAT_STR = "Format: (Value)(unitStr)x / : (Value)(unitStr)";

Television* ScreenFactory::CreateTelevision(InputHandler& input, OutputHandler& output)
{
    output.CustomMsg("Enter desired dimensions. " + std::string(FORMAT_STR), true);
    output.CustomMsg("Available unit options - mm, cm, m. Default - mm",    true);

    auto rawDimensions = ExtractRawDimensions(input);
    while (rawDimensions.first.empty() || rawDimensions.second.empty() || rawDimensions.isAspect)
    {
        output.CustomMsg("Please enter valid dimensions " + std::string(FORMAT_STR), true);
        rawDimensions = ExtractRawDimensions(input);
    }

    Dimension   dimensions = input.GetDimensionsFromInput(rawDimensions.first, rawDimensions.second);
    if (dimensions.isAspect())
    {
        output.ErrMsg("A screen of type Television cannot be created with aspect ratio dimensions!");
        return nullptr;
    }

    Television* television = new Television(dimensions);

    if (!television)
        throw std::runtime_error("Failed to allocate television object!");

    return television;
}

LEDWall* ScreenFactory::CreateLedWall(InputHandler& input, OutputHandler& output)
{
    output.CustomMsg("Enter panel dimensions. " + std::string(FORMAT_STR), true);
    output.CustomMsg("or (Value):(Value)", true);
         
    auto rawPanelDimensions = ExtractRawDimensions(input);
    while (rawPanelDimensions.first.empty() || rawPanelDimensions.second.empty() ||
           rawPanelDimensions.isAspect)
    {
        output.CustomMsg("Please enter valid panel dimensions " + std::string(FORMAT_STR), true);
        rawPanelDimensions = ExtractRawDimensions(input);
    }

    Dimension panelDimensions = input.GetDimensionsFromInput(rawPanelDimensions.first,
                                rawPanelDimensions.second);
    if (panelDimensions.isAspect())
    {
        output.ErrMsg("A screen of type Television cannot be created with aspect ratio dimensions!");
        return nullptr;
    }

    output.CustomMsg("Enter desired max dimensions. " + std::string(FORMAT_STR), true);
    output.CustomMsg("or (Value):(Value)", true);

    auto rawDimensions = ExtractRawDimensions(input);
    while (rawDimensions.first.empty() || rawDimensions.second.empty())
    {
        output.CustomMsg("Please enter valid dimensions " + std::string(FORMAT_STR), true);
        rawDimensions = ExtractRawDimensions(input);
    }

    Dimension dimensions = input.GetDimensionsFromInput(rawDimensions.first,
                                                             rawDimensions.second);

    LEDWall* ledWall = nullptr;
    if (rawDimensions.isAspect)
        ledWall = new LEDWall(panelDimensions, dimensions, new AspectStrategy());
    else
        ledWall = new LEDWall(panelDimensions ,dimensions, new FreeformStrategy());

    if (!ledWall)
        throw std::runtime_error("Failed to allocate led wall object!");

    return ledWall;
}

ScreenFactory::RawDimensions ScreenFactory::ExtractRawDimensions(InputHandler& input)
{
    RawDimensions result = RawDimensions("", "", false);

    std::regex dim_regex(R"(^(\d+)(mm|cm|m)\s*[xX]?\s*(\d+)(mm|cm|m)$)");
    std::regex aspect_ratio_regex(R"(^\s*(\d+)\s*[:]?\s*(\d+)\s*$)");

    std::string userInput = input.GetUserInput(false,true);

    std::smatch match;

    std::string firstDimension, secondDimension;
    size_t i = 1;

    if (std::regex_match(userInput, match, dim_regex))
    {
        if (i + 1 < match.size())
            firstDimension = match[i].str() + match[i + 1].str();
        else
            return result;

        i++;
        i++;

        if (i + 1 < match.size())
            secondDimension = match[i].str() + match[i + 1].str();
        else
            return result;

        result.first  = firstDimension;
        result.second = secondDimension;

        return result;
    }
    else if (std::regex_match(userInput, match, aspect_ratio_regex))
    {
        if (i + 1 < match.size())
        {
            firstDimension  = match[i++].str();
            secondDimension = match[i].str();

            result.first    = firstDimension;
            result.second   = secondDimension;
            result.isAspect = true;

            return result;
        }
    }

    return result;
}
