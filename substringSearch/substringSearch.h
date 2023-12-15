#pragma once

#include <stdlib.h>

// Rabin-Karp substring search;
// return index of first substring character if substring is in s, otherwise -1
int substringSearch(const char* const string, const size_t stringLength, const char* const substring, const size_t substringLength);
