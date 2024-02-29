#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "commentsLexer.h"

#define MAIN_FILE_NAME "input.txt"

ConsoleError runProgram(void)
{
    FILE* file = NULL;
    fopen_s(&file, MAIN_FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Error occurred during file openning\n");
        return fileOpenningError;
    }

    char* comments = getComments(file);

    fclose(file);

    if (comments == NULL)
    {
        printf("Error occurred\n");
        return commentsGettingError;
    }

    printf("Comments:\n");
    printf("%s", comments);

    free(comments);
    return success;
}