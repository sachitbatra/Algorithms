#include<stdio.h>
#include<stdlib.h>

void floyds(int*, int);
int minimum(int, int);

int main()
{
	int nVertices, input;

   //printf("Enter the number of vertices: ");
   scanf("%d", &nVertices);
   
   int *adjMatrix = (int*)malloc(nVertices * nVertices * sizeof(int));

   //printf("Input Adjacency Matrix\n");
   for (int row = 0; row < nVertices; row++)
   {
       for (int col = 0; col < nVertices; col++)
       {
           //printf("[%c][%c]: ", (row + 65), (col + 65));
           scanf("%d", &input);
           *(adjMatrix + row*nVertices + col) = input;
       }
   }
   
   floyds(adjMatrix, nVertices);   
   
   for (int row = 0; row < nVertices; row++)
   {
   	printf("\n");
      for (int col = 0; col < nVertices; col++)
      {
          printf("%d\t", *(adjMatrix + row*nVertices + col));
      }
   }
}

void floyds(int *adjMatrix, int nVertices)
{
	for (int k = 0; k < nVertices; k++)
	{
		for (int row = 0; row < nVertices; row++)
		{
			for (int col = 0; col < nVertices; col++)
			{
				*(adjMatrix + row*nVertices + col) = minimum((*(adjMatrix + row*nVertices + col)), (*(adjMatrix + row*nVertices + k) + *(adjMatrix + k*nVertices + col)));
			}
		}
	}
}

int minimum(int a, int b)
{
    if (a < b)
    {
        return a;
    }

    else
    {
        return b;
    }
}
