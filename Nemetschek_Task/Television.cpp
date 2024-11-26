#include <string>
#include "Television.h"

Television::Television()
    : Screen()
{}

Television::Television(const Dimension& other)
    : Screen(other)
{}

std::string Television::ToString() const
{
    return "Television: " + Screen::ToString();
}
