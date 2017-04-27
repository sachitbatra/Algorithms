#include<stdio.h>
#include<stdlib.h>

//Stack
typedef struct stackNode
{
    int data;
    struct stackNode *next;
}stack;

void push(stack **, int);
int pop(stack**);

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
    stack *stackNode = NULL;

    push(&stackNode, vertex);
    visited[vertex] = 1;

    //printf("\nPushed %c\n", (vertex + 65));

    while(stackNode != NULL)
    {
        int curVertex = pop(&stackNode);
        //printf("\nPopped %c\n", (curVertex + 65));
        printf("%c ", (curVertex+65));

        for (int col = 0; col < nVertices; col++)
        {
            if (*(adjMatrix + curVertex*nVertices + col) == 1)
            {
                if (visited[col] == 0)
                {
                    visited[col] = 1;
                    push(&stackNode, col);
                    //printf("\nPushed %c\n", (col + 65));
                }
            }
        }
    }
}

void push(stack **node, int value)
{
    stack *link = (stack*)malloc(sizeof(stack));
    link->data = value;
    link->next = (*node);
    (*node) = link;
}

int pop(stack **node)
{
    if ((*node) == NULL)
    {
        printf("Underflow Error!\n");
        return -1;
    }

    stack *temp = (*node);
    int retVal = temp->data;
    (*node) = (*node)->next;
    return retVal;
}
