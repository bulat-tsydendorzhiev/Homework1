#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "algorithm.h"

#define INFINITY SIZE_MAX

static size_t getNumberOfNearestCity(const size_t capitalNumber, size_t** states, size_t** graph, bool* visited,
    const size_t numberOfCities, const size_t numberOfCapitals)
{
    size_t minimumDistance = INFINITY, numberOfTheNearestCity = INFINITY;
    size_t stateCity = states[capitalNumber][0];

    for (size_t i = 0; i < numberOfCities - numberOfCapitals && stateCity != 0; i++)
    {
        stateCity = states[capitalNumber][i];
        for (size_t currentCity = 1; currentCity < numberOfCities + 1; currentCity++)
        {
            if (!visited[currentCity])
            {
                if (graph[stateCity][currentCity] < minimumDistance)
                {
                    minimumDistance = graph[stateCity][currentCity];
                    numberOfTheNearestCity = currentCity;
                }
            }
        }
    }

    return numberOfTheNearestCity;
}

void distributeCities(size_t** graph, size_t numberOfCities, size_t** states, size_t numberOfCapitals, bool* visited)
{
    size_t numberOfRemainedCities = numberOfCities - numberOfCapitals;
    while (numberOfRemainedCities > 0)
    {
        for (size_t capitalNumber = 0; capitalNumber < numberOfCapitals; ++capitalNumber)
        {
            size_t numberOfNearestCity = getNumberOfNearestCity(capitalNumber, states, graph,
                visited, numberOfCities, numberOfCapitals);

            if (numberOfNearestCity == INFINITY)
            {
                continue;
            }

            size_t insertIndex = 0;
            while (states[capitalNumber][insertIndex] != 0)
            {
                ++insertIndex;
            }
            states[capitalNumber][insertIndex] = numberOfNearestCity;
            visited[numberOfNearestCity] = true;
            --numberOfRemainedCities;
        }
    }
}

void printStates(const size_t* const* const states, const size_t numberOfStates)
{
    printf("States and their cities:\n");
    for (size_t i = 0; i < numberOfStates; ++i)
    {
        printf("State %Iu: ", i + 1);
        size_t currentCity = 0;
        while (states[i][currentCity] != 0)
        {
            printf("%Iu ", states[i][currentCity]);
            ++currentCity;
        }
        printf("\n");
    }
}