#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "substringSearch.h"

bool tests(void)
{
    const char string[] = "The Rabin-Karp algorithm is a string search algorithm that looks for a pattern, that is, a substring, in the text using hashing.";
    const size_t stringLength = sizeof(string) / sizeof(string[0]);
    const char substrings[][20] = { "a", "string", "Rabin-", "algorithm that", "ng." };
    const size_t substringsLengths[] = {1, 6, 6, 14, 3};
    const int expectedResults[] = { 5, 31, 4, 43, 125};

    for (size_t i = 0; i < 5; ++i)
    {
        const int findResult = substringSearch(string, stringLength, substrings[i], substringsLengths[i]);
        if (findResult != expectedResults[i])
        {
            return false;
        }
    }
    return true;
}