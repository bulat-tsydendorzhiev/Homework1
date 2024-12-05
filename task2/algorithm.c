#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"

static void dfs(int currentVertex, int** graph, bool* const visited, const size_t numberOfVertexes)
{
    visited[currentVertex] = true;
    for (int i = 0; i < numberOfVertexes; i++) {
        if (graph[currentVertex][i] == 1 && !visited[i])
        {
            dfs(i, graph, visited, numberOfVertexes); 
        }
    }
}

int** findComponents(const Graph* const graph, size_t* const numberOfComponents)
{
    const size_t numberOfVertexes = getNumberOfVertexes(graph);
    bool* visited = (bool*)calloc(numberOfVertexes, sizeof(bool));
    if (visited == NULL)
    {
        return NULL;
    }
    int** components = (int**)calloc(numberOfVertexes, sizeof(int*));
    if (components == NULL)
    {
        free(visited);
        return NULL;
    }
    for (size_t i = 0; i < numberOfVertexes; ++i)
    {
        components[i] = (int*)calloc(numberOfVertexes, sizeof(int));
        if (components[i] == NULL)
        {
            free(visited);
            free(components);
            return NULL;
        }
    }

    *numberOfComponents = 0;
    for (size_t i = 0; i < numberOfVertexes; ++i) {
        if (!visited[i])
        { 
            int* currComponent = (int*)calloc(numberOfVertexes, sizeof(int));
            if (currComponent  == NULL)
            {
                free(visited);
                free(components);
                return NULL;
            }

            size_t numberOfVerticals = 0;
            dfs(i, getIncidenceMatrix(graph), visited, numberOfVertexes);
            for (size_t j = 0; j < numberOfVertexes; ++j)
            {
                if (visited[j])
                {
                    currComponent[numberOfVerticals] = j;
                    visited[j] = false;
                    ++numberOfVerticals;
                }
            }
            for (int j = 0; j < numberOfVerticals; j++) {
                components[*numberOfComponents][j] = currComponent[j];
            }
            ++(*numberOfComponents);
        }
    }
    return components;
}

void printComponents(const int*const *const components, const size_t numberOfComponents)
{
    printf("Components and their vertexes:\n");
    for (size_t i = 0; i < numberOfComponents; ++i)
    {
        printf("Component %Iu: ", i + 1);
        for (size_t j = 0; j < numberOfComponents; ++j)
        {
            printf("%d ", components[i][j]);
            
        }
        printf("\n");
    }
}
