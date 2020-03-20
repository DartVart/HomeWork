#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//This method sorts in descending order
void quickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement - leftElement < 1)
        return;

    int upIterator = leftElement;
    int downIterator = rightElement;
    int middleIndex = (leftElement + rightElement) / 2;
    int middle = array[middleIndex];

    while (upIterator < downIterator)
    {
        while (array[upIterator] > middle)
        {
            upIterator++;
        }

        while (array[downIterator] < middle)
        {
            downIterator--;
        }

        if (upIterator <= downIterator)
        {
            swap(&array[upIterator], &array[downIterator]);
            upIterator++;
            downIterator--;
        }
    }

    quickSort(array, upIterator, rightElement);
    quickSort(array, leftElement, downIterator);
}

int main()
{
    int sizeOfInputArray = 0;
    printf("Enter the array size: ");
    scanf("%d", &sizeOfInputArray);

    int* inputArray = (int*) malloc(sizeOfInputArray * sizeof(int));
    printf("Enter the integer elements of the array: ");
    for (int i = 0; i < sizeOfInputArray; i++)
    {
        scanf("%d", &inputArray[i]);
    }

    quickSort(inputArray, 0, sizeOfInputArray - 1);

    for (int i = 0; i < sizeOfInputArray - 1; i++)
    {
        if (inputArray[i] == inputArray[i + 1])
        {
            printf("The maximum repeating element: %d.", inputArray[i]);
            free(inputArray);
            return 0;
        }
    }

    printf("There is no repeating element.");
    free(inputArray);
    return 0;
}