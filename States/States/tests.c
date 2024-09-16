#include "tests.h"
#include "Graph.h"

#define NUMBER_OF_CORRECT_TESTS 4
#define MAX_LENGTH_OF_TEST_FILE_NAME 10
#define MAX_NUMBER_OF_STATES 5
#define MAX_NUMBER_OF_CITIES_IN_STATES 7

static bool compareCities(const Graph* const graph, const size_t expectedStates[MAX_NUMBER_OF_STATES][MAX_NUMBER_OF_CITIES_IN_STATES],
    const size_t numberOfCities, const size_t numberOfStates)
{
    for (size_t i = 0; i < numberOfStates; ++i)
    {
        for (size_t j = 0; j < numberOfCities - numberOfStates + 2; ++j)
        {
            if (getStateCity(graph, i, j) != expectedStates[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

static bool checkTestCase(const char* const fileName, const size_t expectedStates[MAX_NUMBER_OF_STATES][MAX_NUMBER_OF_CITIES_IN_STATES])
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return false;
    }

    Graph* graph = NULL;
    const GraphErrorCode errorInit = initGraph(file, &graph);
    if (errorInit)
    {
        fclose(file);
        return false;
    }
    fclose(file);

    distributeCities(graph);

    const bool testResult = compareCities(graph, expectedStates, getNumberOfCities(graph), getNumberOfCapitals(graph));
    deleteGraph(&graph);
    return testResult;
}

bool runTests(void)
{
    const bool inputTestError = checkTestCase("test1.txt", NULL) != false || checkTestCase("test2.txt", NULL) != false;
    if (inputTestError)
    {
        printf("Input test failed\n");
        return false;
    }

    const size_t expectedStates[NUMBER_OF_CORRECT_TESTS][MAX_NUMBER_OF_STATES][MAX_NUMBER_OF_CITIES_IN_STATES] =
    { 
         { {1, 2, 3} },
         { {1}, {2}, {3}, {4}, {5} },
         { {1, 2, 3}, {4, 5} },
         { {1, 3, 5, 7}, {4, 6, 2} }
    };
    const char fileNames[NUMBER_OF_CORRECT_TESTS][MAX_LENGTH_OF_TEST_FILE_NAME] = { "test3.txt", "test4.txt", "test5.txt", "test6.txt" };

    for (size_t i = 0; i < NUMBER_OF_CORRECT_TESTS; ++i)
    {
        const bool testPassed = checkTestCase(fileNames[i], expectedStates[i]);
        if (!testPassed)
        {
            printf("Test %Iu failed\n", i + 1);
            return false;
        }
    }

    return true;
}