#pragma once
#include <map>
#include <string>
#include <unordered_map>

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

	std::string GetUserInput() const;
	INPUT_TYPE  GetUserInputType(const std::string& input) const;

	~InputHandler() = default;
private:
	static const TypeStringMap m_typeToStr;
};


