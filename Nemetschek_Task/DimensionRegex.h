#pragma once
#include <regex>
#include <string>

class DimensionRegex
{
public:
    static std::smatch MatchDimensionRegex(const std::string& input);
    static std::smatch MatchAspectRegex(const std::string& input);

    static std::string ExtractDimension(const std::smatch& match, size_t index, size_t offset);
};

