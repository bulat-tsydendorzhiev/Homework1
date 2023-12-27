#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRAPH_SIZE 5
#define EXPRESSION_SIZE 100

typedef enum
{
    success,
    fileError
} ErrorCode;

int main()
{
    char* dotExePath = getenv("GraphVizDot");
    if (dotExePath == NULL)
    {
        dotExePath = "C:\\Program Files\\Graphviz\\bin\\dot.exe"; // default path to dot.exe
    }

    const char matrix[GRAPH_SIZE][GRAPH_SIZE] = { {0, 1, 0, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 0, 1, 0},
                                                  {0, 0, 0, 0, 1},
                                                  {1, 0, 0, 0, 0} };
    char dotFileName[] = "graph.dot";

    FILE* file = NULL;
    fopen_s(&file, dotFileName, "w");
    if (file == NULL)
    {
        return fileError;
    }

    fprintf(file, "digraph Graph {\n");
    fprintf(file, "    node[fontname=\"Consolas\"]\n");
    fprintf(file, "    layout=neato;\n");
    for (size_t i = 0; i < GRAPH_SIZE; ++i)
    {
        for (size_t j = 0; j < GRAPH_SIZE; ++j)
        {
            if (matrix[i][j] == 1)
            {
                fprintf(file, "    %Iu -> %Iu;\n", i, j);
            }
        }
    }
    fprintf(file, "}\n");

    fclose(file);

    char command[EXPRESSION_SIZE] = "";
    char pngFileName[] = "graph.png";
    sprintf_s(command, EXPRESSION_SIZE, "\"%s\" -Tpng %s -o %s", dotExePath, dotFileName, pngFileName);
    system(command);

    sprintf_s(command, EXPRESSION_SIZE, "start %s", pngFileName);
    system(command);

    return success;
}