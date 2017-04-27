#include<stdio.h>
#include<stdlib.h>

//Setting maximum edge length as 10000
int maxLength = 10000;

int prims(int*, int);

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

    printf("\nThe minimum Cost of the tree is: %d.\n", prims(adjMatrix, nVertices));

    return 0;
}

int prims(int *adjMatrix, int nVertices)
{
    int minimumCost = 0;
    int verticesVisited = 1; //Starting from vertex 0

    int *visited = (int*)malloc(sizeof(int) * nVertices);
    for (int vertex = 0; vertex < nVertices; vertex++)
    {
        visited[vertex] = 0;
    }

    for (int row = 0; row < nVertices; row++)
    {
        for (int col = 0; col < nVertices; col++)
        {
            if (*(adjMatrix + row*nVertices + col) == 0)
            {
                *(adjMatrix + row*nVertices + col) = maxLength;
            }
        }
    }

    visited[0] = 1;
    while(verticesVisited < nVertices)
    {
        int edgeStart, edgeEnd;
        int min = maxLength;
        for (int row = 0; row < nVertices; row++)
        {
            for (int col = 0; col < nVertices; col++)
            {
                if (*(adjMatrix + row*nVertices + col) < min)
                {
                    if ((visited[row] != 0) && (visited[col] == 0))
                    {
                        min = *(adjMatrix + row*nVertices + col);
                        edgeStart = row;
                        edgeEnd = col;
                    }
                }
            }
        }

        printf("\nEdge:[%c] - [%c]: cost: %d", (edgeStart + 65), (edgeEnd + 65), min);
        minimumCost += min;
        verticesVisited++;
        visited[edgeEnd] = 1;

        *(adjMatrix + edgeStart*nVertices + edgeEnd) = maxLength;
        *(adjMatrix + edgeEnd*nVertices + edgeStart) = maxLength;
    }

    return minimumCost;
}
