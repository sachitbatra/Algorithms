#include<stdio.h>
#include<stdlib.h>

void quickSort(int*, int, int);
int partition(int*, int, int);
void swap (int*, int*);

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

    quickSort(inputArray, 0, (inputSize-1));

    printf("The sorted array is:\n");
    for (int i = 0; i<inputSize; i++)
    {
        printf("%d ", inputArray[i]);
    }

    return 0;
}

void quickSort(int *inputArray, int low, int high)
{
    if (low < high)
    {
        int part = partition(inputArray, low, high);
        quickSort(inputArray, low, (part-1));
        quickSort(inputArray, (part+1), high);
    }
}

int partition(int *inputArray, int low, int high)
{
    int pivotVal = inputArray[low];
    int greaterPart = low + 1;

    for (int i=(low + 1); i<=high; i++)
    {
        if (inputArray[i] < pivotVal)
        {
            swap(&inputArray[i], &inputArray[greaterPart++]);
        }
    }
    greaterPart--;

    swap(&inputArray[low], &inputArray[greaterPart]);
    return (greaterPart);
}

void swap (int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
