#include <stdio.h>

#include "console.h"
#include "dataInit.h"
#include "substringSearch.h"

ErrorCode runProgram(void)
{
    char* string = getStringFromFile("text.txt");
    if (string == NULL)
    {
        return outOfMemory;
    }

    printf("Enter substring: ");
    char* substring = getString();
    if (substring == NULL)
    {
        free(string);
        return outOfMemory;
    }

    const int index = substringSearch(string, substring);
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