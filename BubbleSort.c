#include<stdio.h>
#include<stdlib.h>

void bubbleSort(int*, int);

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

    bubbleSort(inputArray, inputSize);

    printf("The sorted array is:\n");
    for (int i = 0; i<inputSize; i++)
    {
        printf("%d ", inputArray[i]);
    }

    return 0;
}

void bubbleSort(int *inputArray, int inputSize)
{
    for (int i=0; i<(inputSize-1); i++)
    {
        int swapFlag = 0;

        for (int j=0; j<(inputSize-i-1); j++)
        {
            if (inputArray[j] > inputArray[j+1])
            {
                swapFlag = 1;
                swap(&inputArray[j], &inputArray[j+1]);
            }
        }

        if (swapFlag == 0)
        {
            break;
        }
    }
}

void swap (int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

