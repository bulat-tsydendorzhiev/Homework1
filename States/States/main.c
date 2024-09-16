#include <stdio.h>

#include "tests.h"
#include "Graph.h"

typedef enum
{
    testsFailed = -1,
    success,
    openningFileError = 3
};

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return testsFailed;
    }

    FILE* file = NULL;
    fopen_s(&file, "mainFile.txt", "r");
    if (file == NULL)
    {
        return openningFileError;
    }

    Graph* graph = NULL;
    const GraphErrorCode errorInit = initGraph(file, &graph);
    if (errorInit)
    {
        fclose(file);
        return errorInit;
    }
    fclose(file);

    distributeCities(graph);
    printStates(graph);

    deleteGraph(&graph);
    return success;
}