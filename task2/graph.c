#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

struct Graph
{
    size_t numberOfVertexes;
    int** incidenceMatrix;
};

Graph* createGraph(const size_t numberOfVertexes)
{
    Graph* newGraph = (Graph*)calloc(1, sizeof(Graph));
    if (newGraph == NULL)
    {
        return NULL;
    }

    newGraph->numberOfVertexes = numberOfVertexes;
    newGraph->incidenceMatrix = (int**)calloc(numberOfVertexes, sizeof(int*));
    if (newGraph->incidenceMatrix == NULL)
    {
        free(newGraph);
        return NULL;
    }

    for (size_t i = 0; i < numberOfVertexes; ++i)
    {
        newGraph->incidenceMatrix[i] = (int*)calloc(numberOfVertexes, sizeof(int));
        if (newGraph->incidenceMatrix[i] == NULL)
        {
            free(newGraph);
            return NULL;
        }
    }
    return newGraph;
}

void func(Graph* graph)
{
    graph->incidenceMatrix[0][0] = 1;
    graph->incidenceMatrix[0][1] = 1;
    graph->incidenceMatrix[0][2] = 0;
    graph->incidenceMatrix[0][3] = 0;
    graph->incidenceMatrix[1][0] = 1;
    graph->incidenceMatrix[1][1] = 1;
    graph->incidenceMatrix[1][2] = 0;
    graph->incidenceMatrix[1][3] = 0;
    graph->incidenceMatrix[2][0] = 0;
    graph->incidenceMatrix[2][1] = 0;
    graph->incidenceMatrix[2][2] = 1;
    graph->incidenceMatrix[2][3] = 1;
    graph->incidenceMatrix[3][0] = 0;
    graph->incidenceMatrix[3][1] = 0;
    graph->incidenceMatrix[3][2] = 1;
    graph->incidenceMatrix[3][3] = 1;
}

void assignValue(Graph* const graph, const size_t numberOfVertex, const size_t numberOfEdge, const int value)
{
    graph->incidenceMatrix[numberOfVertex][numberOfEdge] = value;
}

size_t getNumberOfVertexes(Graph* graph)
{
    return graph->numberOfVertexes;
}

int** getIncidenceMatrix(Graph* graph)
{
    return graph->incidenceMatrix;
}

void deleteGraph(Graph** graph)
{
    for (size_t i = 0; i < (*graph)->numberOfVertexes; ++i)
    {
        free((*graph)->incidenceMatrix[i]);
    }
    free(*graph);
    *graph = NULL;
}