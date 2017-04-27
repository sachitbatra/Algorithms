#include<stdio.h>
#include<stdlib.h>

int knapsack(int, int*, int*, int);
int maximum(int, int);

int main()
{
    int numItems;
    //printf("Enter the number of items: ");
    scanf("%d", &numItems);

    int *weights = (int*)malloc(sizeof(int) * (numItems+1));
    for (int i=1; i<=numItems; i++)
    {
        int input;
        //printf("Enter the weight of item %d: ", i);
        scanf("%d", &input);
        weights[i] = input;
    }

    int *values = (int*)malloc(sizeof(int) * (numItems+1));
    for (int i=1; i<=numItems; i++)
    {
        int input;
        //printf("Enter the value of item %d: ", i);
        scanf("%d", &input);
        values[i] = input;
    }

    int capacity;
    //printf("Enter the capacity: ");
    scanf("%d", &capacity);

    printf("%d", knapsack(numItems, weights, values, capacity));
    
    return 0;
}

int knapsack(int numItems, int *weights, int *values, int capacity)
{
    int *knapsackMat = (int*)malloc((numItems+1) * (capacity+1) * sizeof(int));

    for (int col = 0; col <= capacity; col++)
    {
        *(knapsackMat + 0*(capacity+1) + col) = 0; //For 0 Items
    }

    for (int row = 0; row <= numItems; row++)
    {
        *(knapsackMat + row*(capacity+1) + 0) = 0; //For 0 Weight
    }

    for (int row = 1; row <= numItems; row++)
    {
        for (int col = 1; col <= capacity; col++)
        {
            int value;

            if (col < weights[row])
            {
                value = *(knapsackMat + (row-1)*(capacity+1) + col);
            }

            else
            {
                value = maximum((*(knapsackMat + (row-1)*(capacity+1) + col)),(*(knapsackMat + (row-1)*(capacity+1) + col - weights[row]) + values[row]));
            }

            *(knapsackMat + (row)*(capacity+1) + col) = value;
        }
    }

    for(int row = 0; row <= numItems; row++)
    {
        printf("\n");
        for (int col = 0; col <= capacity; col++)
        {
            printf("%d\t", *(knapsackMat + row*(capacity+1) + col));
        }
    }
    printf("\n");
    
    int col = capacity;    
    for (int row = numItems; row > 0; row--)
    {
    	if (col <= 0)
    		break;
    	
	 	if (*(knapsackMat + row*(capacity+1) + col) != *(knapsackMat + (row-1)*(capacity+1) + col))
	 	{
	 		printf("%d ", row);
	 		col -= weights[row];
	 	}
    }
    
    printf("\n");

    return (*(knapsackMat + (numItems)*(capacity+1) + capacity));
}

int maximum(int a, int b)
{
    if (a > b)
    {
        return a;
    }

    else
    {
        return b;
    }
}
