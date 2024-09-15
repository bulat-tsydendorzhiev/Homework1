#pragma once

#include <stdbool.h>

// Сheck whether a string is specified by a regular expression: [A-Za-z] ([A-Za-z] | [0-9] | _ ) *
// return true if specified
bool isRightString(const char* const string);
