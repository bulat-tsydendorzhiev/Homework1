#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "substringSearch.h"

#define NUMBER_OF_TESTS 6
#define MAX_TEST_SUBSTRING_LENGTH 20

bool runTests(void)
{
    const char testString[] = "The Rabin-Karp algorithm is a string search algorithm that looks for a pattern, that is, a substring, in the text using hashing.";
    const char testSubstrings[NUMBER_OF_TESTS][MAX_TEST_SUBSTRING_LENGTH] = { "a", "pattern,", "Rabin-", "algorithm that", "ng.", "my god"};
    const int expectedResults[NUMBER_OF_TESTS] = { 5, 71, 4, 44, 125, -1};

    for (size_t i = 0; i < NUMBER_OF_TESTS; ++i)
    {
        const int findResult = substringSearch(testString, testSubstrings[i]);
        if (findResult != expectedResults[i])
        {
            printf("Test %Iu failed\n", i + 1);
            return false;
        }
    }
    return true;
}