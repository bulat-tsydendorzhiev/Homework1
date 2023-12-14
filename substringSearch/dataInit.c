#include <stdio.h>

#include "dataInit.h"

char* getString(size_t* length)
{
    *length = 0;
    size_t capacity = 1;
    char* string = (char*)calloc(capacity, sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }

    char character = getchar();
    while (character != '\n')
    {
        string[(*length)++] = character;
        if (*length >= capacity)
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
    string[*length] = '\0';

    return string;
}

char* getStringFromFile(const char* const fileName, size_t* length)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }

    *length = 0;
    size_t capacity = 1;
    char* string = (char*)calloc(capacity, sizeof(char));
    if (string == NULL)
    {
        fclose(file);
        return NULL;
    }

    char character = getc(file);
    while (!feof(file))
    {
        string[(*length)++] = character;
        if (*length >= capacity)
        {
            char* temp = (char*)realloc(string, 2 * capacity * sizeof(char));
            if (temp == NULL)
            {
                return NULL;
            }
            string = temp;
            capacity *= 2;
        }
        character = getc(file);
    }
    string[*length] = '\0';

    fclose(file);
    return string;
}
