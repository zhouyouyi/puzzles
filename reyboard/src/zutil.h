#ifndef ZUTIL_H
#define ZUTIL_H

#include <iostream>
#include <string>

// removes leading and trailing white spaces
// boost has a more resilient implementation though
std::string trim(const std::string& str, const std::string& whitespace = " \t");

#endif
