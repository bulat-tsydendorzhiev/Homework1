#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    testsFailed = -1,
    success,
    initializingError
} ErrorCode;

void replaceRepeatedCharacter(char* string, size_t* const length)
{
    size_t index = 0;
    char previous = '\0';
    for (size_t i = 0; i < *length; ++i)
    {
        if (previous != string[i])
        {
            string[index] = string[i];
            ++index;
            previous = string[i];
        }
    }
    *length = index;
}

bool isCorrectString(const char* const string, const size_t length)
{
    for (size_t i = 1; i < length; ++i)
    {
        if (string[i - 1] == string[i])
        {
            return false;
        }
    }
    return true;
}

bool tests(void)
{
    char testCases[][10] = { "", "a", "\n\n", "aafgbbba" };
    size_t lengths[] = {0, 1, 2, 8};

    for (size_t i = 0; i < 4; i++)
    {
        replaceRepeatedCharacter(testCases[i], &lengths[i]);
        if (!isCorrectString(testCases[i], lengths[i]))
        {
            return false;
        }
    }
    return true;
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

void printResult(const char* const string, const size_t stringLength)
{
    printf("The resulting string: ");
    for (size_t i = 0; i < stringLength; ++i)
    {
        printf("%c", string[i]);
    }
    printf("\n");
}

int main()
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return testsFailed;
    }

    size_t stringLength = 0;
    char* string = getStringFromFile("input.txt", &stringLength);
    if (string == NULL)
    {
        return initializingError;
    }

    replaceRepeatedCharacter(string, &stringLength);
    printResult(string, stringLength);

    free(string);
    return success;
}