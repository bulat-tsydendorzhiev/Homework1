#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "algorithm.h"

#define TEST_FAILED -1

typedef enum
{
    ok,
    loadError,
    outOfMemory,
    openFileError
} ErrorCodes;

bool isEqual(const int** result, const size_t numberOfComponents)
{
    const int expected[4][4] = { {0,1,0,0},
                                 {0,1,0,0},
                                 {2,3,0,0},
                                 {2,3,0,0} };
    for (size_t i = 0; i < numberOfComponents; ++i)
    {
        for (size_t j = 0; j < numberOfComponents; ++j)
        {
            if (result[i][j] != expected[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool test(void)
{
    const size_t numberOfVertexes = 4;
    Graph* graph = createGraph(numberOfVertexes);
    if (graph == NULL)
    {
        return false;
    }

    const int testCaseGraph[4][4] = { {1,1,0,0},
                                    {1,1,0,0},
                                    {0,0,1,1},
                                    {0,0,1,1} };

    for (size_t i = 0; i < numberOfVertexes; ++i)
    {
        for (size_t j = 0; j < numberOfVertexes; ++j)
        {
            assignValue(graph, i, j, testCaseGraph[i][j]);
        }
    }

    

    size_t numberOfComponents = 0;
    const int** components = findComponents(graph, &numberOfComponents);
    if (components == NULL)
    {
        deleteGraph(&graph);
        return false;
    }

    return isEqual(components, numberOfComponents);
}

int main()
{
    const bool testPassed = test();
    if (!testPassed)
    {
        return TEST_FAILED;
    }
    return ok;
}