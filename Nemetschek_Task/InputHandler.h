#pragma once
#include <map>
#include <string>
#include <unordered_map>
#include <regex>
#include "Dimension.h"

class InputHandler
{
public:
	enum class INPUT_TYPE
	{
		CREATE,
		PRINT,
		HELP,
		EXIT,
		DATA,
		INVALID
	};

	typedef std::unordered_map<std::string , INPUT_TYPE>  TypeStringMap;

	InputHandler() = default;

	Dimension   GetDimensionsFromInput(std::string width, std::string height) const;
	std::string GetUserInput(bool removeSpace = true, bool lower = true) const;
	INPUT_TYPE  GetUserInputType(const std::string& input) const;

	~InputHandler() = default;
private:
	static const TypeStringMap m_typeToStr;
};


