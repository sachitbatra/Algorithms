#include<stdio.h>
#include<stdlib.h>

void breadthFirst(int*, int);
void componentTraversal(int*, int*, int, int);

//Queue
typedef struct node
{
	int data;
	struct node *next;

}NODE;
void qinsert(int, NODE **, NODE **);
int qremove(NODE **, NODE **);

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

    breadthFirst(adjMatrix, nVertices);

    return 0;
}

void breadthFirst(int *adjMatrix, int nVertices)
{
    int *visited = (int*)malloc(sizeof(int) * nVertices);
    for (int vertex = 0; vertex<nVertices; vertex++)
    {
        visited[vertex] = 0;
    }

    int componentCount = 0;

    printf("Breadth First Traversal is: ");
    for (int vertex = 0; vertex < nVertices; vertex++)
    {
        if (visited[vertex] == 0)
        {
            componentCount++;
            componentTraversal(adjMatrix, visited, nVertices, vertex);
        }
    }

    printf("\nThe number of connected components is: %d\n", componentCount);
}

void componentTraversal(int *adjMatrix, int *visited, int nVertices, int vertex)
{
    NODE *front, *rear;
    front = rear = NULL;

    qinsert(vertex, &front, &rear);
    visited[vertex] = 1;
    //printf("\nInserted %d.\n", vertex); //Debugging

    while(front != NULL)
    {
        int curVertex = qremove(&front, &rear);

        //printf("\nRemoved %d.\n", curVertex); //Debugging
        printf("%c ", (curVertex + 65));
        //visited[curVertex] = 1; //Not valid because it could lead to an element to be added in the queue twice.

        int row = curVertex;
        for (int col = 0; col < nVertices; col++)
        {
            if(*(adjMatrix + row*nVertices + col) == 1)
            {
                if (visited[col] == 0)
                {
                    qinsert(col, &front, &rear);
                    visited[col] = 1;
                    //printf("\nInserted %d.\n", col); //Debugging
                }
            }
        }
    }
}

//Inserting into Queue
void qinsert(int x, NODE **f, NODE **r)
{
	NODE *temp;

    temp = (NODE*)malloc(sizeof(NODE));
    temp->data = x;
    temp->next = NULL;

    if(*f==NULL)
        *f = *r = temp;

    else
    {
		(*r)->next = temp;
        *r = temp;
    }
}

//Removing from Queue
int qremove(NODE **f, NODE **r)
{

    NODE *q;
	q = *f;

    int x;

    if(q==NULL)
    {
        printf("QUEUE EMPTY \n");
        return -1;
    }
    else
    {
        x = q->data;

        if(*f==*r)
			*f = *r = NULL;

        else
            *f = q->next;

        free(q);
        return x;
    }
}
