#include <iostream>
#include <cmath>
#include <regex>
#include "InputHandler.h"

const std::unordered_map<std::string, InputHandler::INPUT_TYPE> InputHandler::m_typeToStr =
{
    {"create", INPUT_TYPE::CREATE},
    {"print",  INPUT_TYPE::PRINT},
    {"help",   INPUT_TYPE::HELP},
    {"exit",   INPUT_TYPE::EXIT}
};

Dimension InputHandler::GetDimensionsFromInput(std::string width, std::string height) const
{
    auto parseDimension = [](const std::string& input) 
        -> std::pair<unsigned, Dimension::Units>
    {
        auto result = std::make_pair(NULL, Dimension::Units::MILLIMETER);
        std::string valuePart;
        std::string unitPart;

        size_t i = NULL;

        while (i < input.size() && 
              (std::isdigit(input[i]) || input[i] == '.' || input[i] == ','))
        {
            valuePart += input[i++];
        }

        while (i < input.size() && std::isalpha(input[i]))
        {
            unitPart += input[i++];
        }

        valuePart.erase(remove_if(valuePart.begin(), valuePart.end(), ::isspace),
                        valuePart.end());
        unitPart.erase(remove_if(unitPart.begin(), unitPart.end(), ::isspace),
                        unitPart.end());

        if (valuePart.empty())
            throw std::invalid_argument("Invalid input: missing numeric value.");

        result.first = round(std::stod(valuePart));

        if (result.first < 0)
            throw std::invalid_argument("Invalid input: failed conversion.");


        if (unitPart == MILLIMETER_STR)
            result.second = Dimension::Units::MILLIMETER;
        else if (unitPart == CENTIMETER_STR)
            result.second = Dimension::Units::CENTIMETER;
        else if (unitPart == METER_STR)
            result.second = Dimension::Units::METER;
        else if(unitPart.empty())
            result.second = Dimension::Units::MILLIMETER;
        else
            throw std::invalid_argument("Invalid unit: must be 'mm', 'cm', or 'm'.");

        return result;
    };

    auto widthParsed  = parseDimension(width);
    auto heightParsed = parseDimension(height);

    return Dimension(widthParsed.first, heightParsed.first, widthParsed.second);
}

std::string InputHandler::GetUserInput(bool removeSpace, bool lower) const
{
    std::string input;
    do
    {
        std::getline(std::cin, input);

    } while (input.empty());

    auto normalizeInputString = [removeSpace,lower](const std::string& str)
    {
        std::string result;

        for (char ch : str)
        {
            auto normalizedCh = lower ? std::tolower(ch) : ch;

            if (removeSpace && std::isspace(ch))
                continue;
            
            result.push_back(std::tolower(ch));
        }
        return result;
    };

    input = normalizeInputString(input);

    return input;
}

InputHandler::INPUT_TYPE InputHandler::GetUserInputType(const std::string& input) const
{
    auto result = m_typeToStr.find(input);
    if (result != m_typeToStr.end())
        return result->second;

    return INPUT_TYPE::INVALID;
}
