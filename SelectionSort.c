#include<stdio.h>
#include<stdlib.h>

void selectionSort(int*, int);

int main()
{
    int inputSize;
    printf("Enter the number of elements: ");
    scanf("%d", &inputSize);

    int *inputArray = (int*)malloc(sizeof(int) * inputSize);
    for (int i = 0; i<inputSize; i++)
    {
        int input;
        printf("Enter element %d: ", (i+1));
        scanf("%d", &input);
        inputArray[i] = input;
    }

    selectionSort(inputArray, inputSize);

    printf("The sorted array is:\n");
    for (int i = 0; i<inputSize; i++)
    {
        printf("%d ", inputArray[i]);
    }

    return 0;
}

void selectionSort(int *inputArray, int inputSize)
{
    for (int i=0; i<(inputSize-1); i++)
    {
        int minimum = i;
        for (int j=(i+1); j<inputSize; j++)
        {
            if (inputArray[j] < inputArray[minimum])
            {
                minimum = j;
            }
        }
        swap(&inputArray[i], &inputArray[minimum]);
    }
}

void swap (int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

