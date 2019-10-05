#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void moveZerosToEnd(int array[], int sizeOfArray)
{
    int indexOfNonzeroElement = 0;
    int indexOfZeroElement = sizeOfArray - 1;

    while (indexOfNonzeroElement < indexOfZeroElement)
    {
        while (array[indexOfNonzeroElement] != 0)
        {
            indexOfNonzeroElement++;
        }

        while (array[indexOfZeroElement] == 0)
        {
            indexOfZeroElement--;
        }

        if (indexOfNonzeroElement < indexOfZeroElement)
        {
            swap(&array[indexOfNonzeroElement], &array[indexOfZeroElement]);
            indexOfNonzeroElement++;
            indexOfZeroElement--;
        }
    }
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

int main()
{
    int sizeOfInputArray = 0;
    printf("Enter the array size: ");
    scanf("%d", &sizeOfInputArray);

    int* inputArray = (int*) calloc(sizeOfInputArray, sizeof(int));
    printf("Enter the integer elements of the array: ");
    for (int i = 0; i < sizeOfInputArray; i++)
    {
        scanf("%d", &inputArray[i]);
    }

    moveZerosToEnd(inputArray, sizeOfInputArray);
    printf("An array whose zeros are moved to the end: ");
    printArray(inputArray, sizeOfInputArray);

    free(inputArray);
    
    return 0;
}