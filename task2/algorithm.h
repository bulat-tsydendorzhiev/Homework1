#pragma once

#include "graph.h"

// Find connected components of graph;
// return them as two-dimensional array
int** findComponents(const Graph* const graph, size_t* const numberOfComponents);

// Print connected components of graph;
void printComponents(const int* const* const components, const size_t numberOfComponents);

