#pragma once
#include <string>
class IDataObject
{
public:
	virtual std::string ToString() const = 0;
	virtual ~IDataObject() = default;
};