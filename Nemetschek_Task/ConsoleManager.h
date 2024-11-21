#pragma once
#include <string>
#include <map>
class ConsoleManager
{
public:
	ConsoleManager();
	ConsoleManager(std::string initialMsg);

	void Initial() const;
	void Options() const;
	void CustomMsg(const std::string& msg) const;
	void ErrMsg(const std::string& msg) const;
	std::string GetUserInput() const;

	~ConsoleManager() = default;
private:
	static const std::map<std::string, std::string> m_optionsToDesc;
	std::string initialMsg;
};

