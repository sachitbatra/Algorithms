#include<stdio.h>
#include<stdlib.h>

void depthFirst(int*, int*, int, int);

int main()
{
    int nVertices, input;

    printf("Enter the number of vertices: ");
    scanf("%d", &nVertices);

    int *adjMatrix = (int*)malloc(nVertices * nVertices * sizeof(int));

    printf("Input Adjacency Matrix\n");
    for (int row = 0; row < nVertices; row++)
    {
        for (int col = 0; col < nVertices; col++)
        {
            printf("[%c][%c]: ", (row + 65), (col + 65));
            scanf("%d", &input);
            *(adjMatrix + row*nVertices + col) = input;
        }
    }

    int *visited = (int*)malloc(sizeof(int) * nVertices);
    for (int vertex = 0; vertex < nVertices; vertex++)
    {
        visited[vertex] = 0;
    }

    int componentCount = 0;
    printf("Depth First Traversal is: ");
    for (int vertex = 0; vertex < nVertices; vertex++)
    {
        if (visited[vertex] == 0)
        {
            componentCount++;
            depthFirst(adjMatrix, visited, nVertices, vertex);
        }
    }

    printf("\nThe number of connected components is: %d\n", componentCount);

    return 0;
}

void depthFirst(int *adjMatrix, int *visited, int nVertices, int vertex)
{
    visited[vertex] = 1;
    printf("%c ", (vertex + 65));

    int row = vertex;
    for (int col = 0; col < nVertices; col++)
    {
        if (*(adjMatrix + row*nVertices + col) == 1)
        {
            if (visited[col] == 0)
            {
                depthFirst(adjMatrix, visited, nVertices, col);
            }
        }
    }
}
