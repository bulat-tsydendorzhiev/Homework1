#include <stdio.h>
#include <stdlib.h>

#include "dataInit.h"

char* getString(void)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)calloc(capacity, sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }

    char character = getchar();
    while (character != '\n')
    {
        string[length++] = character;
        if (length >= capacity)
        {
            char* temp = (char*)realloc(string, 2 * capacity * sizeof(char));
            if (temp == NULL)
            {
                return NULL;
            }
            string = temp;
            capacity *= 2;
        }
        character = getchar();
    }
    string[length] = '\0';

    return string;
}