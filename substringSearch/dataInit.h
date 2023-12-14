#pragma once

#include <stdlib.h>

// Get string from user
char* getString(size_t* length);

// Get string from file
char* getStringFromFile(const char* const fileName, size_t* length);
