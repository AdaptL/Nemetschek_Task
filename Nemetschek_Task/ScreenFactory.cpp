#include <regex>
#include "ScreenFactory.h"
#include "AspectStrategy.h"
#include "FreeformStrategy.h"
#include "DimensionRegex.h"

const char* ScreenFactory::FORMAT_STR = "Format: (Value)(unitStr) x / : (Value)(unitStr)";

Dimension ScreenFactory::GetValidDimensions(InputHandler& input, OutputHandler& output, const std::string& prompt)
{
    output.CustomMsg(prompt + " " + std::string(FORMAT_STR), true);
    output.CustomMsg("Available unit options - mm, cm, m.", true);

    auto rawDimensions = ExtractRawDimensions(input);
    while (rawDimensions.first.empty()  || 
           rawDimensions.second.empty() || 
           rawDimensions.isAspect)
    {
        output.CustomMsg("Please enter valid dimensions " + std::string(FORMAT_STR), true);
        rawDimensions = ExtractRawDimensions(input);
    }

    Dimension dimensions;
    try
    {
        dimensions = input.GetDimensionsFromInput(rawDimensions.first, rawDimensions.second);
    }
    catch (...)
    {
        throw; 
    }

    if (dimensions.isAspect())
    {
        throw std::invalid_argument("Cannot create object with aspect ratio dimensions!");
    }

    return dimensions;
}

Television* ScreenFactory::CreateTelevision(InputHandler& input, OutputHandler& output)
{
    try
    {
        Dimension dimensions = GetValidDimensions(input, output, "Enter desired dimensions.");

        auto television = new Television(dimensions);
        return television;  
    }
    catch (const std::exception& e)
    {
        output.CustomMsg(e.what());
        return nullptr;
    }
    catch (...)
    {
        return nullptr;
    }
}

LEDWall* ScreenFactory::CreateLedWall(InputHandler& input, OutputHandler& output)
{
    try
    {
        Dimension panelDimensions = GetValidDimensions(input, output, "Enter panel dimensions.");

        output.CustomMsg("Enter desired max dimensions. " + std::string(FORMAT_STR), true);
        output.CustomMsg("or (Value):(Value) for aspect ratio", true);

        auto rawMaxDimensions = ExtractRawDimensions(input);
        while (rawMaxDimensions.first.empty() || rawMaxDimensions.second.empty())
        {
            output.CustomMsg("Please enter valid dimensions " + std::string(FORMAT_STR), true);
            rawMaxDimensions = ExtractRawDimensions(input);
        }

        Dimension maxDimensions = input.GetDimensionsFromInput(rawMaxDimensions.first, rawMaxDimensions.second);

        LEDWall* ledWall;
        if (rawMaxDimensions.isAspect)
        {
            Dimension aspectDimension(Dimension::AspectRatio(maxDimensions.GetWidth(),
                maxDimensions.GetHeight()));
            ledWall = new LEDWall(panelDimensions, maxDimensions, new AspectStrategy());
        }
        else
            ledWall = new LEDWall(panelDimensions, maxDimensions, new FreeformStrategy());

        return ledWall;  
    }
    catch (const std::exception& e)
    {
        output.CustomMsg(e.what());
        return nullptr;
    }
    catch (...)
    {
        return nullptr;
    }
}


ScreenFactory::RawDimensions ScreenFactory::ExtractRawDimensions(InputHandler& input)
{
    RawDimensions result = RawDimensions("", "", false);

    std::string userInput = input.GetUserInput(false,true);

    std::string firstDimension, secondDimension;
    size_t i = 1;

    std::smatch match = DimensionRegex::MatchDimensionRegex(userInput);

    if (!match.empty())
    {
        size_t regexOffset = 2;

        if (i + regexOffset < match.size())
            firstDimension = DimensionRegex::ExtractDimension(match, i, regexOffset);
        else
            return result;

        i += regexOffset + 1;

        if (i + regexOffset < match.size())
            secondDimension = DimensionRegex::ExtractDimension(match, i, regexOffset);
        else
            return result;

        result.first = firstDimension;
        result.second = secondDimension;

        return result;
    }

    match = DimensionRegex::MatchAspectRegex(userInput);

    if (!match.empty())
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
