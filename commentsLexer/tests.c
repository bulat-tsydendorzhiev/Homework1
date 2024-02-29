#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tests.h"
#include "commentsLexer.h"

#define TEST_FILE_NAME_LENGTH 10
#define MAX_LENGTH_OF_TEST_COMMENT 33

static bool isEqualStrings(const char* const string1, const char* const string2)
{
    size_t i = 0;
    for (; string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }

    return string1[i + 1] == '\0';
}

bool runTests(void)
{
    const char testFilesNames[][TEST_FILE_NAME_LENGTH] = { "test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt" };
    const char expectedResults[][MAX_LENGTH_OF_TEST_COMMENT] = { "", "/*simple comment*/", "/*more than one row\ncomment*/", "/*more than*//*one/comment*/", "/*opened comment" };
    for (size_t i = 0; i < 5; ++i)
    {
        FILE* testFile = NULL;
        fopen_s(&testFile, testFilesNames[i], "r");
        if (testFile == NULL)
        {
            return false;
        }

        char* comments = getComments(testFile);

        fclose(testFile);

        if (comments == NULL)
        {
            return false;
        }
        if (!isEqualStrings(comments, expectedResults[i]))
        {
            free(comments);
            return false;
        }
        free(comments);
    }
    return true;
}