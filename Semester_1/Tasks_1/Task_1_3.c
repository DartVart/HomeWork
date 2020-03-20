#include <stdio.h>

const int maxSizeOfArray = 1000;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverseArray(int array[], int sizeOfArray)
{
    for (int i = 0, j = sizeOfArray - 1; i < j; i++, j--)
    {
        swap(&array[i], &array[j]);
    }
}

void swapPartsOfArray(int array[], int sizeOfFirstPart, int sizeOfSecondPart)
{
    reverseArray(array, sizeOfFirstPart);
    reverseArray(&array[sizeOfFirstPart], sizeOfSecondPart);
    reverseArray(array, sizeOfFirstPart + sizeOfSecondPart);
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

int main(int argc, char* argv[])
{
    int sizeOfFirstPart = 0;
    int sizeOfSecondPart = 0;
    int sizeOfInputArray = 0;

    printf("Enter the sizes of the first and seconds parts of the array to be changed: ");
    scanf("%d%d", &sizeOfFirstPart, &sizeOfSecondPart);
    sizeOfInputArray = sizeOfFirstPart + sizeOfSecondPart;

    int inputArray[maxSizeOfArray];

    printf("Enter integer elements of an array of length %d: ", sizeOfInputArray);
    for (int i = 0; i < sizeOfInputArray; i++)
    {
        scanf("%d", &inputArray[i]);
    }

    swapPartsOfArray(inputArray, sizeOfFirstPart, sizeOfSecondPart);

    printf("The modified array: ");
    printArray(inputArray, sizeOfInputArray);

    return 0;
}