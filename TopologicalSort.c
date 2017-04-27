#include<stdio.h>
#include<stdlib.h>

int topoIndex;
int *topoArray;
void topoSort(int*, int*, int, int);

int main()
{
    int nVertices, input;

    printf("Enter the number of vertices: ");
    scanf("%d", &nVertices);

    int *adjMatrix = (int*)malloc(nVertices * nVertices * sizeof(int));
    topoArray = (int*)malloc(nVertices * sizeof(int));
    topoIndex = nVertices - 1;

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

    for (int vertex = 0; vertex < nVertices; vertex++)
    {
        if (visited[vertex] == 0)
        {
            topoSort(adjMatrix, visited, nVertices, vertex);
        }
    }

    printf("Topological Sort is: ");

    for (int vertex = 0; vertex < nVertices; vertex++)
    {
        printf("%c ", topoArray[vertex] + 65);
    }

    return 0;
}

void topoSort(int *adjMatrix, int *visited, int nVertices, int vertex)
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
                topoSort(adjMatrix, visited, nVertices, col);
            }
        }
    }

    topoArray[topoIndex--] = vertex;
}
