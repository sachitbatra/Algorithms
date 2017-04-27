#include<stdio.h>
#include<stdlib.h>

void warshall(int**, int);

int main()
{
	int nVertices, input;

   printf("Enter the number of vertices: ");
   scanf("%d", &nVertices);
   
   int **adjMat;
	adjMat = (int**)malloc((nVertices+1) * sizeof(int*));

	for(int i = 0; i < (nVertices + 1); i++)
	{
  		adjMat[i] = (int*)malloc(nVertices * nVertices * sizeof(int));
  	}

   printf("Input Adjacency Matrix\n");
   for (int row = 0; row < nVertices; row++)
   {
       for (int col = 0; col < nVertices; col++)
       {
           scanf("%d", &input);
           *(adjMat[0] + row*nVertices + col) = input;
       }
   }
   
   warshall(adjMat, nVertices);
   
   for (int row = 0; row < nVertices; row++)
   {
   	 printf("\n");
   
       for (int col = 0; col < nVertices; col++)
       {
           printf("%d\t", *(adjMat[nVertices] + row*nVertices + col));
       }
   }
   
   return 0;
}

void warshall(int **adjMat, int nVertices)
{
	for (int k = 1; k<= nVertices; k++)
	{
		for (int row = 0; row < nVertices; row++)
		{
			for (int col = 0; col < nVertices; col++)
			{
				*(adjMat[k] + row*nVertices + col) = (*(adjMat[k-1] + row*nVertices + col)) || ((*(adjMat[k-1] + row*nVertices + (k-1))) && (*(adjMat[k-1] + (k-1)*nVertices + col)));
			}
		}
	}
}
