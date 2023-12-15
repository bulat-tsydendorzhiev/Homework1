#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    testsFailed = -1,
    success,
    openFileError
} ErrorCode;

bool tests(void)
{
    const char testCases[][10] = { "", "", "", "", "" };

    for (size_t i = 0; i < 5; i++)
    {

    }
}

int main()
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return testsFailed;
    }

    FILE* file = NULL;
    fopen_s(&file, "input.txt", "r");
    if (file == NULL)
    {
        return openFileError;
    }

    printf("The resulting string: ");
    char previous = ' ';
    while (!feof(file))
    {
        char current = getc(file);
        if (current != previous)
        {
            printf("%c", current);
            previous = current;
        }
    }
    printf("\n");

    fclose(file);
    return success;
}