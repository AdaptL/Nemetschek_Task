#pragma once
#include <string>
#include <map>
#include "InputHandler.h"

#define DEFAULT_INITIAL_MSG "Welcome! Type (help) to get a list of options!"

class OutputHandler
{
public:
	typedef InputHandler::INPUT_TYPE          InputType;
	typedef std::map<InputType, std::string>  DescriptionMap;
	typedef DescriptionMap*                   DescriptionMapPtr;

	OutputHandler();
	OutputHandler(std::string initialMsg);

	OutputHandler(const OutputHandler& other);
	OutputHandler(OutputHandler&& other) noexcept;

	OutputHandler& operator=(const OutputHandler& other);
	OutputHandler& operator=(OutputHandler&& other) noexcept;

	std::string GetDesc(InputType type) const;
	std::string GetInitial() const;

	void SetInitial(const std::string& msg);
	bool SetDescription(InputType type, const std::string& desc);

	void Initial() const;
	void Options() const;
	void PrintDataObject(const IDataObject& obj);
	void CustomMsg(const std::string& msg, bool endl = true) const;
	void ErrMsg(const std::string& msg) const;

	~OutputHandler();
private:
	DescriptionMapPtr m_inputsDesc;
	std::string       m_initialMsg; 
};


