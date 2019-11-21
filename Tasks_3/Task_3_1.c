#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int* createArrayUsingConsole(int* sizeOfArray)
{
    printf("Enter the array size: ");
    scanf("%d", sizeOfArray);

    int* array = (int*) calloc(*sizeOfArray, sizeof(int));
    printf("Enter the integer elements of the array: ");
    for (int i = 0; i < *sizeOfArray; i++)
    {
        scanf("%d", &array[i]);
    }

    return array;
}

void printArray(int array[], int sizeOfArray)
{
    printf("{");
    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("%d}", array[sizeOfArray - 1]);

}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getIndexOfMinimumElement(int array[], int firstIndex, int secondIndex)
{
    return (array[firstIndex] < array[secondIndex]) ? firstIndex : secondIndex;
}

void siftElement(int heap[], int indexOfElement, int sizeOfHeap)
{
    int indexOfLeftChild = indexOfElement * 2 + 1;
    int indexOfRightChild = indexOfElement * 2 + 2;
    int indexOfMinimumChild = 0;
    bool needSwap = false;

    if (indexOfRightChild < sizeOfHeap)
    {
        indexOfMinimumChild = getIndexOfMinimumElement(heap, indexOfRightChild, indexOfLeftChild);
        if (heap[indexOfElement] > heap[indexOfMinimumChild])
        {
            needSwap = true;
        }
    }
    else if (indexOfLeftChild < sizeOfHeap &&
             heap[indexOfElement] > heap[indexOfLeftChild])
    {
        indexOfMinimumChild = indexOfLeftChild;
        needSwap = true;
    }

    if (needSwap)
    {
        swap(&heap[indexOfMinimumChild], &heap[indexOfElement]);
        siftElement(heap, indexOfMinimumChild, sizeOfHeap);
    }
}

//This method sorts in descending order
void heapSort(int array[], int sizeOfArray)
{
    int indexOfElementWithoutChild = sizeOfArray / 2 - 1;
    for (int i = indexOfElementWithoutChild; i >= 0; i--)
    {
        siftElement(array, i, sizeOfArray);
    }

    for (int i = sizeOfArray - 1; i > 0; i--)
    {
        swap(&array[i], &array[0]);
        siftElement(array, 0, i);
    }
}


int main()
{
    int sizeOfInputArray = 0;
    int* inputArray = createArrayUsingConsole(&sizeOfInputArray);

    heapSort(inputArray, sizeOfInputArray);

    printf("Sorted array: \n");
    printArray(inputArray, sizeOfInputArray);

    free(inputArray);

    return 0;
}