#include <stdlib.h>

#include "Graph.h"

#define INFINITY SIZE_MAX

struct Graph
{
    size_t numberOfCities;
    size_t** distanceBetweenCities;
    size_t numberOfCapitals;
    size_t** states;
    bool* visited;
};

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
            for (size_t j = 0; j < i; ++j)
            {
                free(newMatrix[j]);
            }
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

static void freeMemory(size_t*** const graph, const size_t numberOfCities, size_t*** const states, const size_t numberOfCapitals, bool** const visited)
{
    deleteMatrix(graph, numberOfCities + 1);
    deleteMatrix(states, numberOfCapitals);
    free(*visited);
    *visited = NULL;
}

void deleteGraph(Graph** graph)
{
    freeMemory(&(*graph)->distanceBetweenCities, (*graph)->numberOfCities, &(*graph)->states, (*graph)->numberOfCapitals, &(*graph)->visited);
    free(*graph);
    *graph = NULL;
}

static GraphErrorCode initCitiesAndDistanceBetweenThem(FILE* const file, Graph* graph, const size_t numberOfRoads)
{
    for (size_t i = 0; i < numberOfRoads; i++)
    {
        size_t firstCity = 0;
        size_t secondCity = 0;
        size_t distance = 0;
        if (fscanf_s(file, "%Iu %Iu %Iu", &firstCity, &secondCity, &distance) != 3 || firstCity == secondCity ||
            firstCity > graph->numberOfCities || secondCity > graph->numberOfCities)
        {
            return scanError;
        }
        graph->distanceBetweenCities[firstCity][secondCity] = distance;
        graph->distanceBetweenCities[secondCity][firstCity] = distance;
    }
    return ok;
}

static GraphErrorCode statesInit(FILE* const file, Graph* graph)
{
    for (size_t i = 0; i < graph->numberOfCapitals; ++i)
    {
        size_t capitalNumber = 0;
        if (fscanf_s(file, "%Iu", &capitalNumber) != 1 || capitalNumber > graph->numberOfCities)
        {
            return scanError;
        }
        graph->states[i][0] = capitalNumber;
        graph->visited[capitalNumber] = true;
    }
    return ok;
}

GraphErrorCode initGraph(FILE* const file, Graph** graph)
{
    *graph = (Graph*)calloc(1, sizeof(Graph));
    if (*graph == NULL)
    {
        return outOfMemory;
    }

    size_t numberOfCities = 0;
    size_t numberOfRoads = 0;
    if (fscanf_s(file, "%Iu", &numberOfCities) != 1 || fscanf_s(file, "%Iu", &numberOfRoads) != 1)
    {
        free(*graph);
        return scanError;
    }

    (*graph)->numberOfCities = numberOfCities;
    (*graph)->distanceBetweenCities = createMatrix(numberOfCities + 1, numberOfCities + 1, INFINITY);
    (*graph)->visited = (bool*)calloc(numberOfCities + 1, sizeof(bool));
    if ((*graph)->distanceBetweenCities == NULL || (*graph)->visited == NULL)
    {
        free((*graph)->visited);
        deleteMatrix(&(*graph)->distanceBetweenCities, numberOfCities);
        free(*graph);
        return outOfMemory;
    }

    const GraphErrorCode errorInitCitiesAndDistanceBetweenThem = initCitiesAndDistanceBetweenThem(file, (*graph), numberOfRoads);
    if (errorInitCitiesAndDistanceBetweenThem)
    {
        free((*graph)->visited);
        deleteMatrix(&(*graph)->distanceBetweenCities, numberOfCities + 1);
        free(*graph);
        return scanError;
    }

    size_t numberOfCapitals = 0;
    if (fscanf_s(file, "%Iu", &numberOfCapitals) != 1 || numberOfCapitals <= 0 || numberOfCapitals > numberOfCities)
    {
        free((*graph)->visited);
        deleteMatrix(&(*graph)->distanceBetweenCities, numberOfCities);
        free(*graph);
        return scanError;
    }

    (*graph)->numberOfCapitals = numberOfCapitals;
    (*graph)->states = createMatrix(numberOfCapitals, numberOfCities - numberOfCapitals + 2, 0);
    if ((*graph)->states == NULL)
    {
        deleteGraph(graph);
        return outOfMemory;
    }

    const GraphErrorCode statesInitError = statesInit(file, (*graph));
    if (statesInitError)
    {
        deleteGraph(graph);
        return scanError;
    }

    return ok;
}

size_t getNumberOfCities(const Graph* const graph)
{
    return graph->numberOfCities;
}

size_t getNumberOfCapitals(const Graph* const graph)
{
    return graph->numberOfCapitals;
}

size_t getStateCity(const Graph* const graph, const size_t stateNumber, const size_t cityNumber)
{
    return graph->states[stateNumber][cityNumber];
}

static size_t getNumberOfNearestCity(const size_t capitalNumber, Graph* graph)
{
    size_t minimumDistance = INFINITY;
    size_t numberOfTheNearestCity = INFINITY;
    size_t stateCity = graph->states[capitalNumber][0];

    for (size_t i = 0; i < graph->numberOfCities - graph->numberOfCapitals && stateCity != 0; ++i)
    {
        stateCity = graph->states[capitalNumber][i];
        for (size_t currentCity = 1; currentCity < graph->numberOfCities + 1; ++currentCity)
        {
            if (!graph->visited[currentCity])
            {
                if (graph->distanceBetweenCities[stateCity][currentCity] < minimumDistance)
                {
                    minimumDistance = graph->distanceBetweenCities[stateCity][currentCity];
                    numberOfTheNearestCity = currentCity;
                }
            }
        }
    }

    return numberOfTheNearestCity;
}

void distributeCities(Graph* graph)
{
    size_t numberOfRemainedCities = graph->numberOfCities - graph->numberOfCapitals;
    while (numberOfRemainedCities > 0)
    {
        for (size_t capitalNumber = 0; capitalNumber < graph->numberOfCapitals; ++capitalNumber)
        {
            const size_t numberOfNearestCity = getNumberOfNearestCity(capitalNumber, graph);

            if (numberOfNearestCity == INFINITY)
            {
                continue;
            }

            size_t insertIndex = 0;
            while (graph->states[capitalNumber][insertIndex] != 0)
            {
                ++insertIndex;
            }
            graph->states[capitalNumber][insertIndex] = numberOfNearestCity;
            graph->visited[numberOfNearestCity] = true;
            --numberOfRemainedCities;
        }
    }
}

void printStates(const Graph* const graph)
{
    printf("States and their cities:\n");
    for (size_t i = 0; i < graph->numberOfCapitals; ++i)
    {
        printf("State %Iu: ", i + 1);
        size_t currentCity = 0;
        while (graph->states[i][currentCity] != 0)
        {
            printf("%Iu ", graph->states[i][currentCity]);
            ++currentCity;
        }
        printf("\n");
    }
}
