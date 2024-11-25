#include <string>
#include "Television.h"

std::string Television::ToString() const
{
    return "Television " + Screen::ToString();
}
