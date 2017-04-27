#include"Graph.h"

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

    if (isCompleteGraph(adjMatrix, nVertices))
    {
        printf("It is a complete graph.\n");
    }
    else
    {
        printf("It is not a complete graph.\n");
    }

    if (isStarGraph(adjMatrix, nVertices))
    {
        printf("It is a star graph.\n");
    }
    else
    {
        printf("It is not a star graph.\n");
    }

    if (isRingGraph(adjMatrix, nVertices))
    {
        printf("It is a ring graph.\n");
    }
    else
    {
        printf("It is not a ring graph.\n");
    }

    /* //Printing the Adjacency Matrix
    for (int row = 0; row < nVertices; row++)
    {
        printf("\n");
        for (int col = 0; col < nVertices; col++)
        {
            printf("%d", *(adjMatrix + row*nVertices + col));
        }
    }*/

    return 0;
}

int isCompleteGraph(int *matrix, int nVert)
{
    for (int row = 0; row < nVert; row++)
    {
        for (int col = 0; col < nVert; col++)
        {
            if (row != col)
            {
                if (*(matrix + row*nVert + col) < 1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int isStarGraph(int *matrix, int nVert)
{
    int nAdjacentVertices = 0;
    int centerVertex = -1;
    int centerVertexFound = 0;
    int adjacentVertex;

    for (int row = 0; row < nVert; row++)
    {
        nAdjacentVertices = 0;
        adjacentVertex = -1;

        for (int col = 0; col < nVert; col++)
        {
            if (row != col)
            {
                if (*(matrix + row*nVert + col) == 1)
                {
                    adjacentVertex = col;
                    nAdjacentVertices++;
                }
            }
        }

        if (nAdjacentVertices == nVert - 1)
        {
            if (centerVertexFound == 0)
            {
                centerVertexFound = 1;
            }

            else
            {
                return 0;
            }
        }

        else if (nAdjacentVertices == 1)
        {
            if (centerVertex == -1)
            {
                centerVertex = adjacentVertex;
            }

            else
            {
                if (adjacentVertex != centerVertex)
                {
                    return 0;
                }
            }
        }

        else
        {
            return 0;
        }
    }

    return 1;
}

int isRingGraph(int *matrix, int nVert)
{
    int startVertex = 0;
    int previousVertex = 0;
    int nextVertex;

    int nAdjacentVertices = 0;

    int *traversedVertices = (int*)malloc(nVert * sizeof(int));
    int nVerticesTraversed = 0;

    for (int col = 0; col < nVert; col++)
    {
        if (*(matrix + 0*nVert + col) == 1)
        {
            nextVertex = col;
            nAdjacentVertices++;
        }
    }

    if (nAdjacentVertices != 2)
    {
        return 0;
    }

    while(nextVertex != startVertex)
    {
        int adjVertex1 = -1;
        int adjVertex2 = -1;

        traversedVertices[nVerticesTraversed++] = nextVertex;

        nAdjacentVertices = 0;
        for (int col = 0; col < nVert; col++)
        {
            if (*(matrix + nextVertex*nVert + col) == 1)
            {
                nAdjacentVertices++;

                if (adjVertex1 == -1)
                {
                    adjVertex1 = col;
                }

                else if (adjVertex2 == -1)
                {
                    adjVertex2 = col;
                }
            }
        }

        if (nAdjacentVertices != 2)
        {
            return 0;
        }

        int tempVertex = nextVertex;

        if (adjVertex1 == previousVertex)
        {
            for (int i = 0; i < nVerticesTraversed; i++)
            {
                if (adjVertex2 == traversedVertices[i])
                {
                    return 0;
                }

                else
                {
                    nextVertex = adjVertex2;
                }
            }
        }

        else if (adjVertex2 == previousVertex)
        {
            for (int i = 0; i < nVerticesTraversed; i++)
            {
                if (adjVertex1 == traversedVertices[i])
                {
                    return 0;
                }

                else
                {
                    nextVertex = adjVertex1;
                }
            }
        }

        else
        {
            return 0;
        }

        previousVertex = tempVertex;
    }

    if (nVerticesTraversed == nVert - 1) //Check to see if all the vertices have been traversed, startVertex not included in variable nVerticesTraversed
    {
        return 1;
    }

    else
    {
        return 0;
    }
}
