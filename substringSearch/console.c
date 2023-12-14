#include <stdio.h>

#include "console.h"
#include "dataInit.h"
#include "substringSearch.h"

int runProgram(void)
{
    size_t stringLength = 0;
    const char* const string = getStringFromFile("mainFile.txt", &stringLength);
    if (string == NULL)
    {
        return outOfMemory;
    }

    printf("Enter substring: ");
    size_t substringLength = 0;
    const char* const substring = getString(&substringLength);
    if (substring == NULL)
    {
        free(string);
        return outOfMemory;
    }

    const int index = substringSearch(string, stringLength, substring, substringLength);
    if (index == -1)
    {
        printf("There is no such substring in string\n");
    }
    else
    {
        printf("Substring is in string with the index %d\n", index);
    }

    free(string);
    free(substring);
    return success;
}