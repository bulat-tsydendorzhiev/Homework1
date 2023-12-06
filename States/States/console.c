#include <stdio.h>
#include <stdbool.h>

#include "console.h"
#include "dataInit.h"
#include "algorithm.h"

int console(void)
{
    FILE* file = NULL;
    fopen_s(&file, "mainFile.txt", "r");
    if (file == NULL)
    {
        return FILE_ERROR;
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
    printStates(states, numberOfCapitals);

    freeMemory(&graph, numberOfCities, &states, numberOfCapitals, &visited);
    return 0;
}