#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    ok,
    scanError,
    outOfMemory
} GraphErrorCode;

typedef struct Graph Graph;

// Init graph from file
GraphErrorCode initGraph(FILE* const file, Graph** graph);

// Delete graph
void deleteGraph(Graph** graph);

// Distribute cities between states
void distributeCities(Graph* graph);

// Print states and their cities
void printStates(const Graph* const graph);

// Return number of cities in graph
size_t getNumberOfCities(const Graph* const graph);

// Return number of caoitals in graph
size_t getNumberOfCapitals(const Graph* const graph);

// Return 
size_t getStateCity(const Graph* const graph, const size_t stateNumber, const size_t cityNumber);
