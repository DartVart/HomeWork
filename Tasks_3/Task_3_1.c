#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int* createArrayUsingConsole(int* sizeOfArray)
{
    bool isCorrectInput = true;
    printf("Enter the array size:");
    isCorrectInput = scanf("%d", sizeOfArray) != 0;
    if (!isCorrectInput || *sizeOfArray <= 0)
    {
        return NULL;
    }

    int* array = (int*) calloc(*sizeOfArray, sizeof(int));
    printf("Enter the integer elements of the array:");
    for (int i = 0; i < *sizeOfArray; i++)
    {
        isCorrectInput = scanf("%d", &array[i]) != 0;
        if (!isCorrectInput)
        {
            return NULL;
        }
    }

    char remainingCharacterInStream = '\0';
    scanf("%c", &remainingCharacterInStream);
    while (remainingCharacterInStream != '\n')
    {
        if (remainingCharacterInStream != ' ' && remainingCharacterInStream != '\t')
        {
            return NULL;
        }
        scanf("%c", &remainingCharacterInStream);
    }

    return array;
}

void printArray(int* array, int sizeOfArray)
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

int getIndexOfMinimumElement(const int* array, int firstIndex, int secondIndex)
{
    return (array[firstIndex] < array[secondIndex]) ? firstIndex : secondIndex;
}

void siftDownElement(int* heap, int indexOfElement, int sizeOfHeap)
{
    int indexOfRightChild = indexOfElement * 2 + 2;
    int indexOfLeftChild = indexOfRightChild - 1;
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
        siftDownElement(heap, indexOfMinimumChild, sizeOfHeap);
    }
}

//This method sorts in descending order
void heapSort(int* array, int sizeOfArray)
{
    int indexOfElementWithoutChild = sizeOfArray / 2 - 1;
    for (int i = indexOfElementWithoutChild; i >= 0; i--)
    {
        siftDownElement(array, i, sizeOfArray);
    }

    for (int i = sizeOfArray - 1; i > 0; i--)
    {
        swap(&array[i], &array[0]);
        siftDownElement(array, 0, i);
    }
}

int main()
{
    int sizeOfInputArray = -1;
    int* inputArray = createArrayUsingConsole(&sizeOfInputArray);

    if (inputArray == NULL && sizeOfInputArray != 0)
    {
        printf("Incorrect input!");
        return -1;
    }
    else if (sizeOfInputArray != 0)
    {
        heapSort(inputArray, sizeOfInputArray);
        printf("Sorted array:\n");
        printArray(inputArray, sizeOfInputArray);
    }
    else
    {
        printf("You entered an empty array.");
    }

    free(inputArray);

    return 0;
}