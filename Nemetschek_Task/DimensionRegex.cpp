#include "DimensionRegex.h"

std::smatch DimensionRegex::MatchDimensionRegex(const std::string& input)
{
    std::regex dim_regex(R"(^(\d+([.,]\d+)?)(mm|cm|m)\s*[xX]\s*(\d+([.,]\d+)?)(mm|cm|m)$)");
    std::smatch match;
    std::regex_match(input, match, dim_regex);
    return match;
}

std::smatch DimensionRegex::MatchAspectRegex(const std::string& input)
{
    std::regex aspect_ratio_regex(R"(^\s*(\d+)\s*[:]?\s*(\d+)\s*$)");
    std::smatch match;
    std::regex_match(input, match, aspect_ratio_regex);
    return match;
}

std::string DimensionRegex::ExtractDimension(const std::smatch& match, size_t index, size_t offset)
{
    if (index + offset < match.size())
        return match[index].str() + match[index + offset].str();
    return "";
}
