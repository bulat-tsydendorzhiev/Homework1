#pragma once

// Graph
typedef struct Graph Graph;

// Create graph
Graph* createGraph(const size_t numberOfVertexes);

// Delete graph
void deleteGraph(Graph** graph);

// Return number of vertexes of graph
size_t getNumberOfVertexes(Graph* graph);

// Return graph incidence matrix
int** getIncidenceMatrix(Graph* graph);

// Assign value to incidence matrix i row and j column
void assignValue(Graph* const graph, const size_t numberOfVertex, const size_t numberOfEdge, const int value);
