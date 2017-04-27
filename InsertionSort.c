#include<stdio.h>
#include<stdlib.h>

void insertionSort(int*, int);

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

    insertionSort(inputArray, inputSize);

    printf("The sorted array is:\n");
    for (int i = 0; i<inputSize; i++)
    {
        printf("%d ", inputArray[i]);
    }
}

void insertionSort(int *inputArray, int inputSize)
{
    for (int i=1; i<inputSize; i++)
    {
        int key = inputArray[i];
        int j = i-1;

        while((key < inputArray[j]) && (j >= 0))
        {
            inputArray[j+1] = inputArray[j];
            j--;
        }

        inputArray[j+1] = key;
    }
}
