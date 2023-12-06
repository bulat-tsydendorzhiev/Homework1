#include <stdlib.h>
#include <stdio.h>

#include "dataInit.h"

#define INFINITY SIZE_MAX

static size_t** createMatrix(const size_t numberOfRows, const size_t numberOfColumns, const size_t defaultValue)
{
    size_t** newMatrix = (size_t**)calloc(numberOfRows, sizeof(size_t*));
    if (newMatrix == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < numberOfRows; i++)
    {
        newMatrix[i] = (size_t*)calloc(numberOfColumns, sizeof(size_t));
        if (newMatrix[i] == NULL)
        {
            return NULL;
        }
        for (size_t j = 0; j < numberOfColumns; j++)
        {
            newMatrix[i][j] = defaultValue;
        }
    }
    return newMatrix;
}

static void deleteMatrix(size_t*** const matrix, size_t numberOfRows)
{
    for (size_t i = 0; i < numberOfRows; i++)
    {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}

static DataInitError graphInit(FILE* const file, size_t** const graph, const size_t numberOfRoads, const size_t numberOfCities)
{
    for (size_t i = 0; i < numberOfRoads; i++)
    {
        size_t firstCity = 0, secondCity = 0, distance = 0;
        if (fscanf_s(file, "%Iu %Iu %Iu", &firstCity, &secondCity, &distance) != 3 || firstCity == secondCity || firstCity > numberOfCities || secondCity > numberOfCities)
        {
            return scanError;
        }
        graph[firstCity][secondCity] = distance;
        graph[secondCity][firstCity] = distance;
    }
    return ok;
}

static DataInitError statesInit(FILE* const file, size_t** states, const size_t numberOfCapitals, const size_t numberOfCities, bool* visited)
{
    for (size_t i = 0; i < numberOfCapitals; i++)
    {
        size_t capitalNumber = 0;
        if (fscanf_s(file, "%Iu", &capitalNumber) != 1 || capitalNumber > numberOfCities)
        {
            return scanError;
        }
        states[i][0] = capitalNumber;
        visited[capitalNumber] = true;
    }
    return ok;
}

void freeMemory(size_t*** const graph, const size_t numberOfCities, size_t*** const states, const size_t numberOfCapitals, bool** const visited)
{
    deleteMatrix(graph, numberOfCities + 1);
    deleteMatrix(states, numberOfCapitals);
    free(*visited);
    *visited = NULL;
}

DataInitError dataInit(FILE* file, size_t* const numberOfCities, size_t*** const graph,
    size_t* const numberOfCapitals, size_t*** const states, bool** const visited)
{
    size_t numberOfRoads = 0;
    if (fscanf_s(file, "%Iu", numberOfCities) != 1 || fscanf_s(file, "%Iu", &numberOfRoads) != 1)
    {
        return scanError;
    }

    *graph = createMatrix(*numberOfCities + 1, *numberOfCities + 1, INFINITY);
    *visited = (bool*)calloc(*numberOfCities + 1, sizeof(bool));
    if (*graph == NULL || *visited == NULL)
    {
        deleteMatrix(graph, *numberOfCities + 1);
        free(*visited);
        return outOfMemoryError;
    }
    const DataInitError graphInitError = graphInit(file, *graph, numberOfRoads, *numberOfCities);
    if (graphInitError)
    {
        deleteMatrix(graph, *numberOfCities + 1);
        free(*visited);
        return scanError;
    }

    if (fscanf_s(file, "%Iu", numberOfCapitals) != 1 || *numberOfCapitals <= 0 || *numberOfCapitals > *numberOfCities)
    {
        deleteMatrix(graph, *numberOfCities);
        free(*visited);
        return scanError;
    }
    *states = createMatrix(*numberOfCapitals, *numberOfCities - *numberOfCapitals + 2, 0);
    if (*states == NULL)
    {
        freeMemory(graph, *numberOfCities, states, *numberOfCapitals, visited);
        return outOfMemoryError;
    }
    const DataInitError statesInitError = statesInit(file, *states, *numberOfCapitals, *numberOfCities, *visited);
    if (statesInitError)
    {
        freeMemory(graph, *numberOfCities, states, *numberOfCapitals, visited);
        return scanError;
    }

    return ok;
}