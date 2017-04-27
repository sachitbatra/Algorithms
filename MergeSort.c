#include<stdio.h>
#include<stdlib.h>

void mergeSort(int*, int, int);
int *mergeArray;
void merge(int*, int, int);

int main()
{
    int inputSize;
    printf("Enter the number of elements: ");
    scanf("%d", &inputSize);

    mergeArray = (int*)malloc(sizeof(int) * inputSize);
    int *inputArray = (int*)malloc(sizeof(int) * inputSize);
    for (int i = 0; i<inputSize; i++)
    {
        int input;
        printf("Enter element %d: ", (i+1));
        scanf("%d", &input);
        inputArray[i] = input;
    }

    mergeSort(inputArray, 0, (inputSize-1));

    printf("The sorted array is:\n");
    for (int i = 0; i<inputSize; i++)
    {
        printf("%d ", inputArray[i]);
    }

    return 0;
}

void mergeSort(int *inputArray, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(inputArray, low, mid);
        mergeSort(inputArray, mid+1, high);
        merge(inputArray, low, high);
    }
}

void merge(int *inputArray, int low, int high)
{
    int mid = (low + high) / 2;
    int firstIndex = low;
    int secondIndex = mid + 1;

    int i = low;

    while((firstIndex <= mid) && (secondIndex <=high))
    {
        if (inputArray[firstIndex] <= inputArray[secondIndex]) // <= is responsible for stable implementation
        {
            mergeArray[i++] = inputArray[firstIndex++];
        }

        else
        {
            mergeArray[i++] = inputArray[secondIndex++];
        }
    }

    while(firstIndex <= mid)
    {
        mergeArray[i++] = inputArray[firstIndex++];
    }

    while(secondIndex <= high)
    {
        mergeArray[i++] = inputArray[secondIndex++];
    }

    for (i = low; i<=high; i++)
    {
        inputArray[i] = mergeArray[i];
    }
}
