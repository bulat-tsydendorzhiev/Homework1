#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "substringSearch.h"

bool runTests(void)
{
    const char testString[] = "The Rabin-Karp algorithm is a string search algorithm that looks for a pattern, that is, a substring, in the text using hashing.";
    const size_t testStringLength = sizeof(testString) / sizeof(testString[0]);
    const char testSubstrings[][20] = { "a", "pattern,", "Rabin-", "algorithm that", "ng." };
    const size_t testSubstringsLengths[] = {1, 8, 6, 14, 3};
    const int expectedResults[] = { 5, 30, 4, 44, 125};

    for (size_t i = 0; i < 5; ++i)
    {
        const int findResult = substringSearch(testString, testStringLength, testSubstrings[i], testSubstringsLengths[i]);
        if (findResult != expectedResults[i])
        {
            return false;
        }
    }
    return true;
}