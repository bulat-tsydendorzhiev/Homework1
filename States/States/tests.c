#include "tests.h"
#include "DataInit.h"
#include "algorithm.h"

static bool compareStates(const size_t* const* const states, const size_t expectedStates[5][7], const size_t numberOfCities, const size_t numberOfStates)
{
    for (size_t i = 0; i < numberOfStates; ++i)
    {
        for (size_t j = 0; j < numberOfCities - numberOfStates + 2; ++j)
        {
            if (states[i][j] != expectedStates[i][j])
            {
                return TEST_FAILED;
            }
        }
    }
    return TEST_PASSED;
}

static int checkTestCase(const char* const fileName, const size_t expectedStates[5][7])
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return 3;
    }

    size_t numberOfCities = 0, numberOfCapitals = 0;
    size_t** graph = NULL;
    size_t** states = NULL;
    bool* visited = NULL;
    const DataInitError errorInit = dataInit(file, &numberOfCities, &graph, &numberOfCapitals, &states, &visited);
    if (errorInit)
    {
        fclose(file);
        return errorInit;
    }
    fclose(file);

    distributeCities(graph, numberOfCities, states, numberOfCapitals, visited);

    const bool testPassed = compareStates(states, expectedStates, numberOfCities, numberOfCapitals);
    freeMemory(&graph, numberOfCities, &states, numberOfCapitals, &visited);
    return testPassed;
}

bool tests(void)
{
    const bool inputTestError = checkTestCase("test1.txt", NULL) != scanError || checkTestCase("test2.txt", NULL) != scanError;
    if (inputTestError)
    {
        return TEST_FAILED;
    }

    const size_t expectedStates[][5][7] = { {{1, 2, 3}},
                                {{1}, {2}, {3}, {4}, {5}},
                                {{1, 2, 3}, {4, 5}},
                                {{1, 3, 5, 7}, {4, 6, 2}} };
    const char fileNames[][10] = { "test3.txt", "test4.txt", "test5.txt", "test6.txt" };

    for (size_t i = 0; i < 4; i++)
    {
        const int testError = checkTestCase(fileNames[i], expectedStates[i]);
        if (testError)
        {
            return testError;
        }
    }

    return TEST_PASSED;
}