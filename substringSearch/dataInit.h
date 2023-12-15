#pragma once

#include <stdlib.h>

// Get string of arbitary length from user
char* getString(size_t* length);

// Get string of arbitary length from file
char* getStringFromFile(const char* const fileName, size_t* length);
